#pragma once
#include "Buffer.h"
#include "Globals.h"

void Buffer::Upload(VkDeviceSize size, void* data)
{
}

void Buffer::Map(VkDeviceSize size, void* data)
{
}

void Buffer::Destroy()
{
}

void Buffer::BindAsVertexBuffer(VkCommandBuffer commandBuffer)
{
	VkBuffer vertexBuffers[] = { m_Buffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
}

void Buffer::BindAsIndexBuffer(VkCommandBuffer commandBuffer)
{
	vkCmdBindIndexBuffer(commandBuffer, m_Buffer,0,VK_INDEX_TYPE_UINT16);
}

uint32_t Buffer::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(Globals::physicalDevice(), &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}
