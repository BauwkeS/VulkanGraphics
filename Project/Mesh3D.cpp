#include "Mesh3D.h"

Mesh3D::Mesh3D()
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
}

void Mesh3D::DestroyMesh()
{
}

void Mesh3D::CreateQuad(float top, float bottom, float left, float right)
{
	std::vector<Vertex> returnVec = {
		{{top,left},{1.0f, 0.0f, 0.0f}},
		{{bottom,right},{1.0f, 0.0f, 0.0f}},
		{{bottom,left},{1.0f, 0.0f, 0.0f}},

		{{top,right},{1.0f, 0.0f, 0.0f}},
		{{bottom,right},{1.0f, 0.0f, 0.0f}},
		{{top,left},{1.0f, 0.0f, 0.0f}},
	};
	m_Vertices = returnVec;
}


void Mesh3D::Draw(VkPipelineLayout pipelineLayout, VkCommandBuffer commandBuffer)
{
    m_VertexBuffer->BindAsVertexBuffer(commandBuffer);
    m_IndexBuffer->BindAsIndexBuffer(commandBuffer);
    vkCmdDrawIndexed(commandBuffer,
        static_cast<uint32_t>(m_Indices.size()),1,0,
        0,0);
}
