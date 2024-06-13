#pragma once
#include <stdexcept>
#include <vulkan/vulkan_core.h>

class Globals
{
private:
    // thanks mat for the help:)
    static inline VkDevice s_Device{};
    static inline VkPhysicalDevice s_PhysicalDevice{};
    //static inline RenderPass* s_pRenderPass{};
   // static inline Swapchain* s_pSwapchain{};
    static inline VkExtent2D s_SwapChainExtent{};
   /* static inline VkQueue s_GraphicsQueue{};
    static inline VkSurfaceKHR s_Surface{};
    static inline VkDescriptorPool s_TexturePool{};
    static inline VkDescriptorSetLayout s_TextureSetLayout{};
    static inline VkCommandPool s_CommandPool{};
    static inline VkDescriptorBufferInfo s_BufferInfo{};*/

    friend class VulkanBase;

public:
    [[nodiscard]] static auto device() { return s_Device; }
    [[nodiscard]] static auto physicalDevice() { return s_PhysicalDevice; }
    // [[nodiscard]] static auto pRenderPass() { return s_pRenderPass; }
   //  [[nodiscard]] static auto pSwapchain() { return s_pSwapchain; }
    [[nodiscard]] static auto swapChainExtent() { return s_SwapChainExtent; }
    //[[nodiscard]] static auto graphicsQueue() { return s_GraphicsQueue; }
    //[[nodiscard]] static auto surface() { return s_Surface; }
    //[[nodiscard]] static auto texturePool() { return s_TexturePool; }
    //[[nodiscard]] static auto textureSetLayout() { return s_TextureSetLayout; }
    //[[nodiscard]] static auto commandPool() { return s_CommandPool; }
    //[[nodiscard]] static auto bufferInfo() { return s_BufferInfo; }
    //[[nodiscard]] static auto SetbufferInfo(VkDescriptorBufferInfo bfferInfo) { s_BufferInfo = bfferInfo; }

   /* static VkCommandBuffer BeginSingleTimeCommands(VkCommandPool commandPool) {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(Globals::device(), &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    static void EndSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(Globals::graphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(Globals::graphicsQueue());

        vkFreeCommandBuffers(Globals::device(), commandPool, 1, &commandBuffer);
    }

    static void CopyBuffer(VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        VkCommandBuffer commandBuffer = BeginSingleTimeCommands(commandPool);

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        EndSingleTimeCommands(commandBuffer, commandPool);
    }

    static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(Globals::physicalDevice(), &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }*/
};
