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
		: m_commandPool{}
	{
	};
	~Command();
	operator VkCommandBuffer() const { return m_Buffer; }

	void CreateCommandPool(uint32_t queueFamilyIndicesGraphicsFamValue);
	void CreateCommandBuffer();

	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,
		VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline,
		std::vector<VkFramebuffer> swapChainFramebuffers, MeshFactory meshF);

	void DestroyCommandPool(std::vector<VkFramebuffer> swapChainFramebuffers);

	VkCommandBuffer GetBuffer() { return m_Buffer; }

	void BufferStart();
	void BufferEnd();

private:
	VkCommandPool m_commandPool;
	VkCommandBuffer m_Buffer{};
};
