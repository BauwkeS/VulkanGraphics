#include "Command.h"
#include "Globals.h"
#include "vulkanbase/VulkanBase.h"

Command::Command()
{
	++s_NumBuffers;
	/*VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = Globals::commandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(Globals::device(), &allocInfo, &m_Buffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}*/
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

//void Command::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,
//	VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline,
//	std::vector<VkFramebuffer> swapChainFramebuffers, MeshFactory meshF)
//{
//	BufferStart();
//
//	VkRenderPassBeginInfo renderPassInfo{};
//	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//	renderPassInfo.renderPass = renderPass;
//	renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
//	renderPassInfo.renderArea.offset = { 0, 0 };
//	renderPassInfo.renderArea.extent = swapChainExtent;
//
//	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
//	renderPassInfo.clearValueCount = 1;
//	renderPassInfo.pClearValues = &clearColor;
//
//	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
//
//	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
//
//	VkViewport viewport{};
//	viewport.x = 0.0f;
//	viewport.y = 0.0f;
//	viewport.width = (float)swapChainExtent.width;
//	viewport.height = (float)swapChainExtent.height;
//	viewport.minDepth = 0.0f;
//	viewport.maxDepth = 1.0f;
//	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
//
//	VkRect2D scissor{};
//	scissor.offset = { 0, 0 };
//	scissor.extent = swapChainExtent;
//	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
//
//	meshF.Draw(commandBuffer);
//
//	vkCmdEndRenderPass(commandBuffer);
//
//	BufferEnd();
//}

void Command::DestroyCommandPool(std::vector<VkFramebuffer> swapChainFramebuffers)
{
	vkFreeCommandBuffers(Globals::device(), Globals::commandPool(), 1, &m_Buffer);
	/*for (auto framebuffer : swapChainFramebuffers) {
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}*/

	vkDestroyCommandPool(Globals::device(), Globals::commandPool(), nullptr);
	/*vkDestroyBuffer(device, m_vertexBuffer, nullptr);
	vkFreeMemory(device, m_vertexBufferMemory, nullptr);*/
}

void Command::BufferStart()
{
	//CreateCommandBuffer();
	//vkResetCommandBuffer(m_Buffer, 0);

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
