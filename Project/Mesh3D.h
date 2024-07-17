#pragma once
#include <memory>
#include <string>

#include <vector>
#include <vulkan/vulkan_core.h>

#include "Buffer.h"
#include "Texture.h"
#include "Vertex.h"

class Mesh3D
{
public:
    struct VertexData
    {
        void* pointer;
        size_t vertexSize;
        uint32_t vertexCount;
    };


    Mesh3D(const std::string& modelPath, const std::string& texturePath);
    ~Mesh3D() = default;

    Mesh3D(Mesh3D&& other) = delete;
    Mesh3D(const Mesh3D& other) = delete;
    Mesh3D operator=(Mesh3D&& other) = delete;
    Mesh3D operator=(const Mesh3D& other) = delete;

	void DestroyMesh();

    void Update();

    void Draw(VkCommandBuffer commandBuffer);

	//ubo stuff
	//const VkDescriptorSetLayout& GetDescriptorSetLayout() { return m_DescriptorSetLayout; }
    void BindDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index);


    void CreateBuffers();

    Texture* GetTexture() { return m_Texture.get(); }

private:
    std::string m_ModelPath;
    glm::mat4 m_ModelMatrix{ 1 };

    std::vector<Vertex3D> m_Vertices{};
    std::vector<uint32_t> m_Indices{};

    std::unique_ptr<Buffer> m_VertexBuffer;
    std::unique_ptr<Buffer> m_IndexBuffer;
    //std::unique_ptr<Buffer> m_StagingBuffer;
   
    //ubo stuff
    //VkDescriptorSetLayout m_DescriptorSetLayout;
    std::unique_ptr<Buffer> m_UBOBuffer;
    //VertexUBO m_UBOSrc;
    //command pool here in Koen's version

    //--
    bool m_Rotate{};
    float m_Angle{};
    glm::vec3 m_Axis{ 0, 1, 0 };
    glm::vec3 m_Center{ 0, 0, 0 };

    void LoadModel();

	//VertexConstant m_vertexConstant;

   /* std::unique_ptr<CommandPoolBuffer> m_CommandPoolBuffer{};

    */
    std::unique_ptr<Texture> m_Texture{};

    void CreateUBOBuffer();
};