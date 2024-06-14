#pragma once
#include "Buffer.h"
#include "Globals.h"

Buffer::Buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
    :m_Size{ size }
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(Globals::device(), &bufferInfo, nullptr, &m_Buffer) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create buffer");
    }

    VkMemoryRequirements memoryRequirements{};
    vkGetBufferMemoryRequirements(Globals::device(), m_Buffer, &memoryRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memoryRequirements.size;
    allocInfo.memoryTypeIndex = FindMemoryType(memoryRequirements.memoryTypeBits,properties);

    if (vkAllocateMemory(Globals::device(), &allocInfo, nullptr, &m_BufferMemory)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate buffer memory");
    }

    vkBindBufferMemory(Globals::device(), m_Buffer, m_BufferMemory, 0);
}

void Buffer::Upload(VkDeviceSize size, void* data)
{
    void* info;
    vkMapMemory(Globals::device(), m_BufferMemory, 0, size, 0, &info);
    memcpy(info, data, size);
    vkUnmapMemory(Globals::device(), m_BufferMemory);
}

void Buffer::Map(VkDeviceSize size, void* data)
{

}

void Buffer::Destroy()
{
    vkDestroyBuffer(Globals::device(), m_Buffer, nullptr);
    vkFreeMemory(Globals::device(), m_BufferMemory, nullptr);
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
