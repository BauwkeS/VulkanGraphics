#pragma once
#include <stdexcept>
#include <vulkan/vulkan_core.h>

#include "Command.h"
#include "Camera.h"
#include "vulkanbase/VulkanBase.h"

class Globals
{
private:
    // thanks mat for the help:)
    static inline VkDevice s_Device{};
    static inline VkPhysicalDevice s_PhysicalDevice{};
    static inline VkRenderPass s_RenderPass{};
    static inline VkDescriptorSetLayout s_UBODescriptorSetLayout{};
    static inline VkDescriptorSetLayout s_TextureDescriptorSetLayout{};
    static inline VkDescriptorPool s_DescriptorPool{};
    static inline VkExtent2D s_SwapChainExtent{};
   // static inline Swapchain* s_pSwapchain{};
    static inline VkQueue s_GraphicsQueue{};
    static inline VkCommandPool s_CommandPool{};
//    static inline Camera* s_pCamera{}; 
   /* static inline VkSurfaceKHR s_Surface{};
    static inline VkDescriptorPool s_TexturePool{};
    static inline VkDescriptorBufferInfo s_BufferInfo{};*/

    friend class VulkanBase;
    friend class Texture;

public:
    [[nodiscard]] static const int MAX_FRAMES_IN_FLIGHT = 2;

    [[nodiscard]] static auto device() { return s_Device; }
    [[nodiscard]] static auto physicalDevice() { return s_PhysicalDevice; }
	[[nodiscard]] static auto renderPass() { return s_RenderPass; }
    [[nodiscard]] static auto UBODescriptorSetLayout() { return s_UBODescriptorSetLayout; }
    [[nodiscard]] static auto TextureDescriptorSetLayout() { return s_TextureDescriptorSetLayout; }
    [[nodiscard]] static auto descriptorPool() { return s_DescriptorPool; }
   //  [[nodiscard]] static auto pSwapchain() { return s_pSwapchain; }
    [[nodiscard]] static auto swapChainExtent() { return s_SwapChainExtent; }
    [[nodiscard]] static auto graphicsQueue() { return s_GraphicsQueue; }
    [[nodiscard]] static auto commandPool() { return s_CommandPool; }
    //[[nodiscard]] static auto camera() { return s_pCamera; }
    //[[nodiscard]] static auto surface() { return s_Surface; }
    //[[nodiscard]] static auto texturePool() { return s_TexturePool; }
    //[[nodiscard]] static auto textureSetLayout() { return s_TextureSetLayout; }
    //[[nodiscard]] static auto bufferInfo() { return s_BufferInfo; }
    //[[nodiscard]] static auto SetbufferInfo(VkDescriptorBufferInfo bfferInfo) { s_BufferInfo = bfferInfo; }

    static VkCommandBuffer BeginSingleTimeCommands(VkCommandPool commandPool) {
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

    static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        /*VkCommandBuffer commandBuffer = BeginSingleTimeCommands(commandPool);

        VkBufferCopy copyRegion{};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        EndSingleTimeCommands(commandBuffer, commandPool);*/

        Command commandB{};

        //commandB.CreateCommandBuffer();

        commandB.BufferStart();
        {
            VkBufferCopy copyRegion{};
            copyRegion.size = size;
            vkCmdCopyBuffer(commandB, srcBuffer, dstBuffer, 1, &copyRegion);
        }
        commandB.BufferEnd();

        commandB.BufferSubmit();
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
    }
};
