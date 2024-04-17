#include "MeshFactory.h"
#include <stdexcept>

void MeshFactory::CreateVertexBuffer()
{
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(vertices[0]) * vertices.size();
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(m_MeshDevice, &bufferInfo, nullptr, &m_vertexBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(m_MeshDevice, m_vertexBuffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(m_MeshDevice, &allocInfo, nullptr, &m_vertexBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}

	vkBindBufferMemory(m_MeshDevice, m_vertexBuffer, m_vertexBufferMemory, 0);

	void* data;
	vkMapMemory(m_MeshDevice, m_vertexBufferMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferInfo.size);
	vkUnmapMemory(m_MeshDevice, m_vertexBufferMemory);
}

void MeshFactory::CreateUniformBuffers()
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

		vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
	}
}

void MeshFactory::Draw(VkCommandBuffer commandBuffer)
{
	VkBuffer vertexBuffers[] = { m_vertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

	vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);

}

uint32_t MeshFactory::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(m_MeshPhysicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

void MeshFactory::DestroyMesh()
{
	//vkDestroyBuffer(m_MeshDevice, m_vertexBuffer, nullptr);
	vkFreeMemory(m_MeshDevice, m_vertexBufferMemory, nullptr);
	if (m_vertexBuffer)
		vkDestroyBuffer(m_MeshDevice, m_vertexBuffer, nullptr);
	if (m_vertexBufferMemory)
		vkFreeMemory(m_MeshDevice, m_vertexBufferMemory, nullptr);
}

void MeshFactory::CreateQuad(float top, float bottom, float left, float right)
{
	std::vector<Vertex> returnVec = {
		{{top,left},{1.0f, 0.0f, 0.0f}},
		{{bottom,right},{1.0f, 0.0f, 0.0f}},
		{{bottom,left},{1.0f, 0.0f, 0.0f}},

		{{top,right},{1.0f, 0.0f, 0.0f}},
		{{bottom,right},{1.0f, 0.0f, 0.0f}},
		{{top,left},{1.0f, 0.0f, 0.0f}},
	};
	vertices = returnVec;
}

void MeshFactory::CreateOval(float x, float y, float radius, float numberOfSegments)
{
	float angle{glm::radians( 360 / numberOfSegments )};

	glm::vec2 middle{ x,y };

	std::vector<Vertex> returnVec{};

	for (int i = 1; i <= numberOfSegments; i++)
	{
		Vertex v1{ { radius * glm::sin(angle*i),radius * glm::cos(angle*i) }, { 1.0f, 0.0f, 0.0f } };
		Vertex v2{ middle,{1.0f, 1.0f, 0.0f} };
		Vertex v3{ { radius * glm::sin(angle*(i+1)),radius * glm::cos(angle*(i+1)) }, { 1.0f, 0.0f, 0.0f } };
		returnVec.emplace_back(v1);
		returnVec.emplace_back(v2);
		returnVec.emplace_back(v3);
	}

	vertices = returnVec;
}

void MeshFactory::CreateRoundedQuad(float top, float bottom, float left,
	float right, float radius, float numberOfSegments)
{
	std::vector<Vertex> returnVec{};

	glm::vec2 middle{ left + (right - left) / 2,bottom + (top - bottom) / 2 };
	float angle{ glm::radians(90 / (numberOfSegments/4)) };

	//top right corner
	for (int i = 1; i <= numberOfSegments/4; i++)
	{
		Vertex v1{ { radius * glm::sin(angle * i),radius * glm::cos(angle * i) }, { 1.0f, 0.0f, 0.0f } };
		Vertex v2{ middle,{1.0f, 1.0f, 0.0f} };
		Vertex v3{ { radius * glm::sin(angle * (i + 1)),radius * glm::cos(angle * (i + 1)) }, { 1.0f, 0.0f, 0.0f } };
		returnVec.emplace_back(v1);
		returnVec.emplace_back(v2);
		returnVec.emplace_back(v3);
	}

	vertices = returnVec;
}
