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

	//old show for textures
	/*VkDescriptorSetLayoutBinding samplerLayoutBinding{};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
	samplerLayoutBinding.pImmutableSamplers = nullptr;*/

	//std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };


	//new show for materials
	std::vector<VkDescriptorSetLayoutBinding> bindings;

	bindings.push_back(uboLayoutBinding);

	//std::vector<VkDescriptorSetLayoutBinding> textureLayoutBindings{};
	for (uint32_t i = 1; i < 5; i++)
	{
		bindings.push_back(VkDescriptorSetLayoutBinding{
			.binding = i,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.descriptorCount = 1,
			.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
			.pImmutableSamplers = nullptr });
	};

	//
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = 2+3;
	layoutInfo.pBindings = bindings.data();
	if (vkCreateDescriptorSetLayout(Globals::device(), &layoutInfo, nullptr, &
		Globals::s_UBODescriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");


	}

	//layoutInfo.pBindings = &samplerLayoutBinding;
	//if (vkCreateDescriptorSetLayout(Globals::device(), &layoutInfo, nullptr, &
	//	Globals::s_TextureDescriptorSetLayout) != VK_SUCCESS) {
	//	throw std::runtime_error("failed to create descriptor set layout!");
	//}

}
