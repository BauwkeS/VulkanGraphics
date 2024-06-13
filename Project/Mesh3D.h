#pragma once
#include <memory>

#include "glm/glm.hpp"
#include <vector>
#include <array>
#include <vulkan/vulkan_core.h>

#include "Buffer.h"

//struct Vertex3D
//{
//    glm::vec3 pos;
//    glm::vec3 color;
//    glm::vec3 normal;
//    glm::vec2 texCoord;
//
//    static VkVertexInputBindingDescription GetBindingDescription();
//    static std::array<VkVertexInputAttributeDescription, 4>
//        GetAttributeDescriptions();
//
//    bool operator==(const Vertex3D& other) const
//    {
//        return pos == other.pos && color == other.color && normal == other.normal
//            && texCoord == other.texCoord;
//    }
//};
struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};


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

private:
    std::vector<Vertex> m_Vertices{};
    std::vector<uint32_t> m_Indices{};

    std::unique_ptr<Buffer> m_VertexBuffer;
    std::unique_ptr<Buffer> m_IndexBuffer;

   /* std::unique_ptr<CommandPoolBuffer> m_CommandPoolBuffer{};

    std::unique_ptr<Texture> m_Texture{};
    glm::mat4 m_ModelMatrix{ 1 };

    bool m_Rotate{};
    float m_Angle{};
    glm::vec3 m_Axis{ 0, 1, 0 };
    glm::vec3 m_Center{ 0, 0, 0 };

    void LoadModel();*/
};