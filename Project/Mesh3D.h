#pragma once
#include <memory>

#include <vector>
#include <vulkan/vulkan_core.h>

#include "Buffer.h"
#include "Vertex.h"

class Mesh3D
{
public:
    Mesh3D();
    ~Mesh3D() = default;

    Mesh3D(Mesh3D&& other) = delete;
    Mesh3D(const Mesh3D& other) = delete;
    Mesh3D operator=(Mesh3D&& other) = delete;
    Mesh3D operator=(const Mesh3D& other) = delete;

	void DestroyMesh();
	void CreateQuad(float top, float bottom, float left, float right);

    void Draw(VkPipelineLayout pipelineLayout, VkCommandBuffer commandBuffer);

	//ubo stuff
	//const VkDescriptorSetLayout& GetDescriptorSetLayout() { return m_DescriptorSetLayout; }
    void BindDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index);


    void CreateBuffers();

private:
    std::vector<Vertex> m_Vertices{};
    std::vector<uint32_t> m_Indices{};

    std::unique_ptr<Buffer> m_VertexBuffer;
    std::unique_ptr<Buffer> m_IndexBuffer;
    std::unique_ptr<Buffer> m_StagingBuffer;
   
    //ubo stuff
    //VkDescriptorSetLayout m_DescriptorSetLayout;
    std::unique_ptr<Buffer> m_UBOBuffer;
    VertexUBO m_UBOSrc;
    //command pool here in Koen's version

    //--

	//VertexConstant m_vertexConstant;

   /* std::unique_ptr<CommandPoolBuffer> m_CommandPoolBuffer{};

    std::unique_ptr<Texture> m_Texture{};
    glm::mat4 m_ModelMatrix{ 1 };

    bool m_Rotate{};
    float m_Angle{};
    glm::vec3 m_Axis{ 0, 1, 0 };
    glm::vec3 m_Center{ 0, 0, 0 };

    void LoadModel();*/

    void CreateUBOBuffer();
};