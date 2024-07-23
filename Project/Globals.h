#pragma once
#include <stdexcept>
#include <vulkan/vulkan_core.h>

#include "Command.h"

class Camera;

class Globals
{
private:
    // thanks mat for the help on thinking to use a global file:)
    static inline VkDevice s_Device{};
    static inline VkPhysicalDevice s_PhysicalDevice{};
    static inline VkRenderPass s_RenderPass{};
    static inline VkDescriptorSetLayout s_UBODescriptorSetLayout{};
    static inline VkDescriptorSetLayout s_TextureDescriptorSetLayout{};
    static inline VkDescriptorPool s_DescriptorPool{};
    static inline VkExtent2D s_SwapChainExtent{};
    static inline VkQueue s_GraphicsQueue{};
    static inline VkCommandPool s_CommandPool{};
    static inline Camera* s_pCamera{};

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
    [[nodiscard]] static auto swapChainExtent() { return s_SwapChainExtent; }
    [[nodiscard]] static auto graphicsQueue() { return s_GraphicsQueue; }
    [[nodiscard]] static auto commandPool() { return s_CommandPool; }
    [[nodiscard]] static auto camera() { return s_pCamera; }


    //global commands that I use too much at too many places
    static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        Command commandB{};

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
