#version 450

layout(set = 1, binding = 0) uniform sampler2D albedoMap;
layout(set = 1, binding = 1) uniform sampler2D normalMap;
layout(set = 1, binding = 2) uniform sampler2D AOMap;
layout(set = 1, binding = 3) uniform sampler2D roughnessMap;
layout(set = 1, binding = 4) uniform sampler2D metallicMap;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

struct Light
{
    vec3 pos;
    vec3 color;
};

const float PI = 3.14159265359;

// Calculates the tangent space normal from the normal map
vec3 CalcNormal()
{
    vec3 normalSampler = texture(normalMap, inTexCoord).rgb * 2.0 - 1.0;

    vec3 N = normalize(inNormal);
    vec3 T = normalize(inColor);
    vec3 B = normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * normalSampler);
}

// GGX/Trowbridge-Reitz Normal Distribution Function
float D_GGX(float dotNH, float roughness)
{
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float denomi = dotNH * dotNH * (alpha2 - 1.0) + 1.0;

    return alpha2 / max(denomi * denomi, 0.000001);
}

// Schlick-Beckmann Geometry Shadowing Function
float GeometryShadowing(float alpha, vec3 N, vec3 X)
{
    float NdotX = max(dot(N, X), 0.0);
    float k = alpha / 2.0;
    float denominator = NdotX * (1.0 - k) + k;

    return NdotX / max(denominator, 0.000001);
}

// Smith Model
float Smith(float alpha, vec3 N, vec3 V, vec3 L)
{
    return GeometryShadowing(alpha, N, V) * GeometryShadowing(alpha, N, L);
}

// Fresnel-Schlick Function
vec3 F(vec3 F0, vec3 V, vec3 H)
{
    float cosTheta = max(dot(V, H), 0.0);
    return F0 + (vec3(1.0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 F_SchlickR(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

// Specular contribution calculation
vec3 SpecularContribution(vec3 L, vec3 V, vec3 N, vec3 F0,
                          float metallic, float roughness, vec3 albedo, vec3 lightColor)
{
    vec3 H = normalize(V + L);
    float dotNH = clamp(dot(N, H), 0.0, 1.0);
    float dotNV = clamp(dot(N, V), 0.0, 1.0);
    float dotNL = clamp(dot(N, L), 0.0, 1.0);

    vec3 color = vec3(0.0);

    if (dotNL > 0.0)
    {
        float D = D_GGX(dotNH, roughness);
        float G = Smith(roughness, N, V, L);
        vec3 F = F(F0, V, H);
        vec3 spec = (D * F * G) / (4.0 * dotNL * dotNV + 0.001);
        vec3 Kd = (vec3(1.0) - F) * (1.0 - metallic);

        color += ((Kd * albedo / PI) + spec) * dotNL * lightColor;
    }

    return color;
}

vec3 PBR()
{
    vec3 normal = CalcNormal();
   // vec3 view = normalize(inCameraPos - inPos);
    vec3 view = normalize(inPos);

    vec3 albedo = texture(albedoMap, inTexCoord).rgb;

    float ao = texture(AOMap, inTexCoord).r;
    float metallic = texture(metallicMap, inTexCoord).r;
    float roughness = texture(roughnessMap, inTexCoord).r;

    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    const int numLights = 2;
    Light lights[numLights];
lights[0].pos = vec3(-10.0, 20.0, -50.0);
lights[0].color = vec3(0.8, 0.8, 1.0);
lights[1].pos = vec3(0.0, 10.0, 5.0);
lights[1].color = vec3(0.8, 0.8, 1.0);


    //Use functions from each light to create full PBR

    vec3 outgoingLight = vec3(0.0);
    for (int i = 0; i < numLights; i++)
    {
        vec3 lightDir = normalize(lights[i].pos - inPos);
        outgoingLight += SpecularContribution(lightDir, view, normal, F0,
                                              metallic, roughness, albedo, lights[i].color);
    }

    vec2 brdf = (0.08 * vec2(max(dot(normal, view), 0.0), roughness));

    vec3 reflection = reflect(-view, normal);
    reflection = vec3(0.8,0.8,1.0);

    vec3 diffuse = 0.7 * albedo;
    vec3 fresnell = F_SchlickR(max(dot(normal, view), 0.0), F0, roughness);
    vec3 specular = reflection * (fresnell * brdf.x + brdf.y);

    vec3 Kd = 1.0 - fresnell;
    Kd *= 1.0 - metallic;

    vec3 ambient = vec3(0.01) + (Kd * diffuse + specular);
    ambient *= ao;

    outgoingLight += ambient;
    return outgoingLight;
}

void main() {
    outColor = vec4(PBR(), 1.0);
}