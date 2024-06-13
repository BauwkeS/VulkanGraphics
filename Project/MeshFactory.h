#pragma once
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>

#include "Vertex.h"


class MeshFactory
{
private:
	VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;

	std::vector<Vertex> vertices{};

	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


public:
	MeshFactory(){};
	
	~MeshFactory() {}
	void DestroyMesh();
	void CreateVertexBuffer();
	void Draw(VkCommandBuffer buffer);

	VkBuffer GetVertextBuffer() const { return m_vertexBuffer; }

	void CreateQuad(float top, float bottom, float left, float right);
	void CreateOval(float x, float y, float radius, float numberOfSegments);
	void CreateRoundedQuad(float top, float bottom, float left, float right, float radius, float numberOfSegments);
};
