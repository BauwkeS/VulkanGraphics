#include "Command.h"
#include "Globals.h"
#include "vulkanbase/VulkanBase.h"

Command::Command()
{
	CreateCommandBuffer();
}

Command::~Command()
{
	vkFreeCommandBuffers(Globals::device(), Globals::commandPool(), 1, &m_Buffer);

	//vkDestroyCommandPool(Globals::device(), Globals::commandPool(), nullptr);
}

void Command::CreateCommandBuffer()
{
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = Globals::commandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(Globals::device(), &allocInfo, &m_Buffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

void Command::DestroyCommandPool(std::vector<VkFramebuffer> swapChainFramebuffers)
{
	vkFreeCommandBuffers(Globals::device(), Globals::commandPool(), 1, &m_Buffer);
	vkDestroyCommandPool(Globals::device(), Globals::commandPool(), nullptr);
}

void Command::BufferStart()
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(m_Buffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
}

void Command::BufferEnd()
{
	if (vkEndCommandBuffer(m_Buffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
}

void Command::BufferSubmit()
{
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_Buffer;

	vkQueueSubmit(Globals::graphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(Globals::graphicsQueue());
}
