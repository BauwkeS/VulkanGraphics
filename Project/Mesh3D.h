#pragma once
#include <memory>
#include <string>

#include <vector>
#include <vulkan/vulkan_core.h>

#include "Buffer.h"
#include "Material.h"
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

	Mesh3D(const std::string& modelPath, const Material* materialPtr, glm::vec3 addToPos);
    ~Mesh3D() = default;

    Mesh3D(Mesh3D&& other) = delete;
    Mesh3D(const Mesh3D& other) = delete;
    Mesh3D operator=(Mesh3D&& other) = delete;
    Mesh3D operator=(const Mesh3D& other) = delete;

    void Update();

    void Draw(VkCommandBuffer commandBuffer);

    void CreateBuffers();
	void BindDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index);

    [[nodiscard]] inline VkDescriptorSet GetMaterialDescriptorSet() const
    {
        return m_pMaterial->GetMaterialDescriptorSet();
    }


private:
    //model info
    std::string m_ModelPath;
    glm::mat4 m_ModelMatrix{ 1 };

    std::vector<Vertex3D> m_Vertices{};
    std::vector<uint32_t> m_Indices{};

    bool m_Rotate{};
    float m_Angle{};
    glm::vec3 m_Axis{ 0, 1, 0 };
    glm::vec3 m_Center{ 0, 0, 0 };

    const Material* m_pMaterial{};

    //buffers
    std::unique_ptr<Buffer> m_VertexBuffer;
    std::unique_ptr<Buffer> m_IndexBuffer;

    //ubo stuff
    std::unique_ptr<Buffer> m_UBOBuffer;

    //functions
    void LoadModel(glm::vec3 addToPos);
    void CreateUBOBuffer();
    static void CalcTangent(std::vector<Vertex3D>& vertices,
        std::vector<uint32_t> indices);
};