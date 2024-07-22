#version 450

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 1, binding = 1) uniform sampler2D dddd;
layout(set = 1, binding = 2) uniform sampler2D AOMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D roughnessMap;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec4 outColor;

//const light vars
const vec3 lightPos = vec3(1.2f, 1.f, 2.f);
const vec3 lightColor = vec3(.8f, .8f, 1.f);

void main() {
    //outColor = texture(texSampler, inTexCoord);

    //PBR calculations

    if (length(inNormal) == 0.f)
    {
        outColor = texture(texSampler, inTexCoord);
        return;
    }

    float ambientStr = 0.1;
    vec3 ambient = ambientStr * lightColor;

    vec3 norm = normalize(inNormal);
    vec3 lightDir = normalize(lightPos - inPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vec3(texture(texSampler, inTexCoord));

    outColor = vec4(result, 1.0);
}