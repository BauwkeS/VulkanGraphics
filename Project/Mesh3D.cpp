#include "Mesh3D.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <OBJL/tiny_obj_loader.h>
#include <unordered_map>


#include "Globals.h"

Mesh3D::Mesh3D(const std::string& modelPath, const std::string& texturePath)
	: m_ModelPath{modelPath}
{
   /* m_Texture = std::make_unique<Texture>(TEXTURE_PATH);
    LoadModel();*/
    //void* data1 = m_Vertices.data();
    //size_t data2 = sizeof(Vertex3D);
    //uint32_t data3 = static_cast<uint32_t>(m_Vertices.size());
    //CommandPoolBuffer::VertexData vertexData(data1,data2,data3);
    /*m_CommandPoolBuffer = std::make_unique<CommandPoolBuffer>(
        CommandPoolBuffer::VertexData(m_Vertices.data(),
            sizeof(Vertex3D),
            static_cast<uint32_t>(m_Vertices.size())),
        m_Indices);*/

   // m_Texture = std::make_unique<Texture>(texturePath);
    //LoadModel();

    m_Texture = std::make_unique<Texture>(texturePath);

    LoadModel();
    CreateBuffers();
   }

void Mesh3D::DestroyMesh()
{
}


void Mesh3D::Draw(VkCommandBuffer commandBuffer)
{
    m_VertexBuffer->BindAsVertexBuffer(commandBuffer);
    m_IndexBuffer->BindAsIndexBuffer(commandBuffer);
    //CreateUBOBuffer();

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

    /*m_StagingBuffer = std::make_unique<Buffer>(
        std::max(vertexBufferSize, indexBufferSize),
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);*/

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

void Mesh3D::LoadModel()
{
    int countV{};
    //tinyobj::attrib_t attrib;
    //std::vector<tinyobj::shape_t> shapes;
    //std::vector<tinyobj::material_t> materials;
    //std::string warn;
    //std::string err;

    //if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, m_ModelPath.c_str()))
    //{
    //    throw std::runtime_error(warn + err);
    //}

    //std::unordered_map<Vertex3D, uint32_t> uniqueVertices{};

    ////for (auto&& shape : shapes)
    ////{
    //    //for (auto&& index : shape.mesh.indices)
    //    //{
    //    //    Vertex3D vertex{};

    //    //    vertex.pos = { attrib.vertices[3 * index.vertex_index + 0],
    //    //                   attrib.vertices[3 * index.vertex_index + 1],
    //    //                   attrib.vertices[3 * index.vertex_index + 2] };

    //    //    vertex.normal = { attrib.normals[3 * index.normal_index + 0],
    //    //                      attrib.normals[3 * index.normal_index + 1],
    //    //                      attrib.normals[3 * index.normal_index + 2] };

    //    //    vertex.texCoord
    //    //        = { attrib.texcoords[2 * index.texcoord_index + 0],
    //    //            1.0f - attrib.texcoords[2 * index.texcoord_index + 1] };

    //    //    vertex.color = { 1.0f, 1.0f, 1.0f };

    //    //    /*if (!uniqueVertices.contains(vertex))
    //    //    {
    //    //        uniqueVertices[vertex]
    //    //            = static_cast<uint32_t>(m_Vertices.size());
    //    //        m_Vertices.push_back(vertex);
    //    //    }*/
    //    //    if (uniqueVertices.count(vertex) == 0) {
    //    //        uniqueVertices[vertex] = static_cast<uint32_t>(m_Vertices.size());
    //    //        m_Vertices.push_back(vertex);
    //    //    }

    //    //    m_Indices.push_back(uniqueVertices[vertex]);
    //    //}


    ////}

    //for (const auto& shape : shapes) {
    //    for (const auto& index : shape.mesh.indices) {
    //        Vertex3D vertex{};

    //        vertex.pos = {
    //            attrib.vertices[3 * index.vertex_index + 0],
    //            attrib.vertices[3 * index.vertex_index + 1],
    //            attrib.vertices[3 * index.vertex_index + 2]
    //        };

    //        vertex.texCoord = {
    //            attrib.texcoords[2 * index.texcoord_index + 0],
    //            1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
    //        };

    //        vertex.color = { 1.0f, 1.0f, 1.0f };

    //        if (!uniqueVertices.contains(vertex)){
    //            uniqueVertices[vertex] = static_cast<uint32_t>(m_Vertices.size());
    //            m_Vertices.push_back(vertex);
    //            ++countV;
    //        }

    //        m_Indices.push_back(uniqueVertices[vertex]);
    //    }
    //}


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

    std::cout << countV << std::endl;
    for (auto vert : uniqueVertices)
    {
	    
	 std::cout << vert.first.pos.x << ", "<< vert.first.pos.y << ", " <<vert.first.pos.z << std::endl;
    }
}
