#include "Material.h"

#include <stdexcept>

#include "vulkanbase/VulkanBase.h"

Material::Material(const std::vector<const Texture*>& textures)
{
    const VkDescriptorSetLayout layout = Globals::TextureDescriptorSetLayout();

    VkDescriptorSetAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocateInfo.descriptorPool = Globals::descriptorPool();
    allocateInfo.descriptorSetCount = 1;
    allocateInfo.pSetLayouts = &layout;

    if (vkAllocateDescriptorSets(Globals::device(),
        &allocateInfo,
        &m_DescriptorSet)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate texture descriptor sets");
    }

    std::vector<VkWriteDescriptorSet> descriptorWrites{};

    for (uint32_t i = 0; i < textures.size(); i++)
    {
        descriptorWrites.push_back(VkWriteDescriptorSet{
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .pNext = nullptr,
            .dstSet = m_DescriptorSet,
            .dstBinding = i,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,

            .pImageInfo = &textures[i]->GetImageInfo(),
            .pBufferInfo = nullptr,
            .pTexelBufferView = nullptr });
    }

    vkUpdateDescriptorSets(Globals::device(),
        descriptorWrites.size(),
        descriptorWrites.data(),
        0,
        nullptr);
}
