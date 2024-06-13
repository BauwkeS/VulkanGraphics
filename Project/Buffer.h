#pragma once
#include <vulkan/vulkan_core.h>

class Buffer
{
public:
    Buffer(VkDeviceSize size, VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties):
        m_Size{size}
	{}
    ~Buffer()=default;

    Buffer(Buffer&& other) = delete;
    Buffer(const Buffer& other) = delete;
    Buffer operator=(Buffer&& other) = delete;
    Buffer operator=(const Buffer& other) = delete;

    VkBuffer GetBuffer() const { return m_Buffer; }
    VkDeviceSize GetBufferSize() const { return m_Size; }
	VkDeviceMemory GetBufferMemory() const { return m_BufferMemory; }

    void Upload(VkDeviceSize size, void* data);
    void Map(VkDeviceSize size, void* data);
    void Destroy();
    void BindAsVertexBuffer(VkCommandBuffer commandBuffer);
    void BindAsIndexBuffer(VkCommandBuffer commandBuffer);

private:
    VkBuffer m_Buffer{};
    VkDeviceSize m_Size{};
    VkDeviceMemory m_BufferMemory{};

    static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};
