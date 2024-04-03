#include "Command.h"
#include "vulkanbase/VulkanBase.h"

void Command::CreateCommandPool(uint32_t queueFamilyIndicesGraphicsFamValue)
{
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndicesGraphicsFamValue;

	if (vkCreateCommandPool(m_Device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
}

void Command::CreateCommandBuffer()
{
	/*commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}*/

	VkCommandBufferAllocateInfo allocInfo{};
	
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = m_commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;
	

	if (vkAllocateCommandBuffers(m_Device, &allocInfo, &m_Buffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

void Command::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,
	VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline,
	std::vector<VkFramebuffer> swapChainFramebuffers, MeshFactory meshF)
{
	BufferStart();

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapChainExtent;

	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapChainExtent.width;
	viewport.height = (float)swapChainExtent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	/*VkBuffer vertexBuffers[] = { m_vertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

	vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);*/

	meshF.Draw(commandBuffer);

	vkCmdEndRenderPass(commandBuffer);

	BufferEnd();
}

//void Command::CreateVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice)
//{
//	VkBufferCreateInfo bufferInfo{};
//	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
//	bufferInfo.size = sizeof(vertices[0]) * vertices.size();
//	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
//	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//
//	if (vkCreateBuffer(device, &bufferInfo, nullptr, &m_vertexBuffer) != VK_SUCCESS) {
//		throw std::runtime_error("failed to create vertex buffer!");
//	}
//
//	VkMemoryRequirements memRequirements;
//	vkGetBufferMemoryRequirements(device, m_vertexBuffer, &memRequirements);
//
//	VkMemoryAllocateInfo allocInfo{};
//	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//	allocInfo.allocationSize = memRequirements.size;
//	allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, physicalDevice);
//
//	if (vkAllocateMemory(device, &allocInfo, nullptr, &m_vertexBufferMemory) != VK_SUCCESS) {
//		throw std::runtime_error("failed to allocate vertex buffer memory!");
//	}
//
//	vkBindBufferMemory(device, m_vertexBuffer, m_vertexBufferMemory, 0);
//
//	void* data;
//	vkMapMemory(device, m_vertexBufferMemory, 0, bufferInfo.size, 0, &data);
//	memcpy(data, vertices.data(), (size_t)bufferInfo.size);
//	vkUnmapMemory(device, m_vertexBufferMemory);
//}
//
//uint32_t Command::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties,
//	VkPhysicalDevice physicalDevice)
//{
//	VkPhysicalDeviceMemoryProperties memProperties;
//	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
//
//	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
//		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
//			return i;
//		}
//	}
//
//	throw std::runtime_error("failed to find suitable memory type!");
//}

void Command::DestroyCommandPool(std::vector<VkFramebuffer> swapChainFramebuffers)
{
	vkFreeCommandBuffers(m_Device, m_commandPool, 1, &m_Buffer);
	/*for (auto framebuffer : swapChainFramebuffers) {
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}*/

	vkDestroyCommandPool(m_Device, m_commandPool, nullptr);
	/*vkDestroyBuffer(device, m_vertexBuffer, nullptr);
	vkFreeMemory(device, m_vertexBufferMemory, nullptr);*/
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
