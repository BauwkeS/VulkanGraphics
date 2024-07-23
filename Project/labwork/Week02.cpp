#include "vulkanbase/VulkanBase.h"
#include "Globals.h"

QueueFamilyIndices VulkanBase::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

void VulkanBase::CreateDescriptorSetLayout()
{
	//ubo stuff
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 1;
	layoutInfo.pBindings = &uboLayoutBinding;

	if (vkCreateDescriptorSetLayout(Globals::device(),
		&layoutInfo,
		nullptr,
		&Globals::s_UBODescriptorSetLayout)
		!= VK_SUCCESS)
	{
		throw std::runtime_error(
			"Failed to create uniform descriptor set layout");
	}

	//texture stuff
	//split up to only update the texture bindings when making materials
	std::vector<VkDescriptorSetLayoutBinding> textureLayoutBindings{};
	for (uint32_t i = 0; i < 5; i++)
	{
		textureLayoutBindings.push_back(VkDescriptorSetLayoutBinding{
			.binding = i,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.descriptorCount = 1,
			.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
			.pImmutableSamplers = nullptr });
	};

	layoutInfo.pBindings = textureLayoutBindings.data();
	layoutInfo.bindingCount = 5;

	if (vkCreateDescriptorSetLayout(Globals::device(),
		&layoutInfo,
		nullptr,
		&Globals::s_TextureDescriptorSetLayout)
		!= VK_SUCCESS)
	{
		throw std::runtime_error(
			"failed to create texture descriptor set layout!");
	}

}
