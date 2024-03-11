#pragma once
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>

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

class MeshFactory
{
public:
	static std::vector<Vertex> CreateQuad(float top, float bottom, float left, float right);
	static std::vector<Vertex> createOval(float x, float y, float radius, float numberOfSegments);
	static std::vector<Vertex> CreateRoundedQuad(float top, float bottom, float left, float right, float radius, float numberOfSegments);
};
