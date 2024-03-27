#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>

class Command
{
public:

	Command()
		: m_commandPool{},
		//m_vertexBuffer{},
		//m_vertexBufferMemory{},
		commandBuffers{}
	{};
	~Command() = default;

	void CreateCommandPool(uint32_t queueFamilyIndicesGraphicsFamValue, VkDevice device);
	void CreateCommandBuffer(VkDevice device);

	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,
		VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline,
		std::vector<VkFramebuffer> swapChainFramebuffers, MeshFactory meshF);

	//void CreateVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice);
	//uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);


	void DestroyCommandPool(VkDevice device, std::vector<VkFramebuffer> swapChainFramebuffers);
	
	std::vector<VkCommandBuffer>& GetCommandBuffers() { return commandBuffers ;}

private:
	VkCommandPool m_commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	/*VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;*/
};
