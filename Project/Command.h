#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>

class Command
{
public:

	Command(VkDevice device)
		: m_commandPool{},
		//m_vertexBuffer{},
		//m_vertexBufferMemory{},
		commandBuffers{},
		m_Device{device}
	{
		/*CreateCommandPool(queueFamilyIndicesGraphicsFamValue, device);
		CreateCommandBuffer(device);*/
	};
	~Command() {
		vkFreeCommandBuffers(m_Device, m_commandPool, 1, &m_Buffer);
		
		vkDestroyCommandPool(m_Device, m_commandPool, nullptr);	
	}
	operator VkCommandBuffer() const { return m_Buffer; }

	void CreateCommandPool(uint32_t queueFamilyIndicesGraphicsFamValue, VkDevice device);
	void CreateCommandBuffer(VkDevice device);

	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,
		VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline,
		std::vector<VkFramebuffer> swapChainFramebuffers, MeshFactory meshF);

	//void CreateVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice);
	//uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);


	void DestroyCommandPool(VkDevice device, std::vector<VkFramebuffer> swapChainFramebuffers);
	
	std::vector<VkCommandBuffer>& GetCommandBuffers() { return commandBuffers ;}

	void BufferStart();
	void BufferEnd();

private:
	VkCommandPool m_commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkCommandBuffer m_Buffer{};
	VkDevice m_Device{};
	//VkDevice m_Device;
	/*VkBuffer m_vertexBuffer;
	VkDeviceMemory m_vertexBufferMemory;*/
};
