#include "Mesh3D.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <OBJL/tiny_obj_loader.h>
#include <unordered_map>


#include "Globals.h"
#include "TimeCount.h"

Mesh3D::Mesh3D(const std::string& modelPath, const Material* materialPtr, glm::vec3 addToPos)
	: m_ModelPath{modelPath},
    m_pMaterial{materialPtr}
{
    LoadModel(addToPos);
    CreateBuffers();
}

void Mesh3D::Update()
{
    if (m_Rotate)
    {
        m_Angle += TimeCount::Delta() * 0.01f;
        m_ModelMatrix = (glm::rotate(glm::translate(glm::mat4(1.f), m_Center),
            m_Angle,
            m_Axis));
    }
}

void Mesh3D::Draw(VkCommandBuffer commandBuffer)
{
    m_VertexBuffer->BindAsVertexBuffer(commandBuffer);
    m_IndexBuffer->BindAsIndexBuffer(commandBuffer);

    vkCmdDrawIndexed(commandBuffer,
        (static_cast<uint32_t>(m_Indices.size())),1,0,
        0,0);
}

void Mesh3D::CreateBuffers()
{
    VkDeviceSize vertexBufferSize = sizeof(Vertex3D) * static_cast<uint32_t>(m_Vertices.size());
    VkDeviceSize indexBufferSize = sizeof(std::decay_t<decltype(*m_Indices.begin())>) * static_cast<uint32_t>(m_Indices.size());

    Buffer stagingBuffer(std::max(vertexBufferSize, indexBufferSize),
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        // fill vertex buffer
    stagingBuffer.Upload(vertexBufferSize, m_Vertices.data());

    m_VertexBuffer = std::make_unique<Buffer>(
        vertexBufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    Globals::CopyBuffer(stagingBuffer.GetBuffer(), m_VertexBuffer->GetBuffer(), vertexBufferSize);

    // fill index buffer
    stagingBuffer.Upload(indexBufferSize, (void*)m_Indices.data());

    m_IndexBuffer = std::make_unique<Buffer>(
        indexBufferSize,
        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    Globals::CopyBuffer(stagingBuffer.GetBuffer(), m_IndexBuffer->GetBuffer(), indexBufferSize);

}

void Mesh3D::CreateUBOBuffer()
{
    m_UBOBuffer = std::make_unique<Buffer>(
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        sizeof(VertexUBO));
}

void Mesh3D::CalcTangent(std::vector<Vertex3D>& vertices, std::vector<uint32_t> indices)
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        Vertex3D& v0{ vertices[indices[i]] };
        Vertex3D& v1{ vertices[indices[i + 1]] };
        Vertex3D& v2{ vertices[indices[i + 2]] };

        const glm::vec3& edge0{ v1.pos - v0.pos };
        const glm::vec3& edge1{ v2.pos - v1.pos };

        const glm::vec2& diffX{
            glm::vec2{v1.texCoord.x - v0.texCoord.x,
                      v2.texCoord.x - v1.texCoord.x}
        };
        const glm::vec2& diffY{
            glm::vec2{v1.texCoord.y - v0.texCoord.y,
                      v2.texCoord.y - v1.texCoord.y}
        };

        float r{ 1.f / (diffX.x * diffY.y - diffX.y * diffY.x) };

        glm::vec3 tangent{ (edge0 * diffY.y - edge1 * diffY.x) * r };
        v0.color += tangent;
        v1.color += tangent;
        v2.color += tangent;
    }
}

void Mesh3D::LoadModel(glm::vec3 addToPos)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;

    if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, m_ModelPath.c_str()))
    {
        throw std::runtime_error(warn + err);
    }

    std::unordered_map<Vertex3D, uint32_t> uniqueVertices{};

    for (auto&& shape : shapes)
    {
        for (auto&& index : shape.mesh.indices)
        {
            Vertex3D vertex{};

            vertex.pos = { attrib.vertices[3 * index.vertex_index + 0],
                           attrib.vertices[3 * index.vertex_index + 1],
                           attrib.vertices[3 * index.vertex_index + 2] };
            vertex.pos = vertex.pos + addToPos;

            vertex.normal = { attrib.normals[3 * index.normal_index + 0],
                              attrib.normals[3 * index.normal_index + 1],
                              attrib.normals[3 * index.normal_index + 2] };

            vertex.texCoord
                = { attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1] };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (!uniqueVertices.contains(vertex))
            {
                uniqueVertices[vertex]
                    = static_cast<uint32_t>(m_Vertices.size());
                m_Vertices.push_back(vertex);
            }

            m_Indices.push_back(uniqueVertices[vertex]);
        }
    }

    CalcTangent(m_Vertices, m_Indices);
}
