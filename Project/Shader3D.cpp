#pragma once
#include "Shader3D.h"
#include "Globals.h"
#include <vulkanbase/VulkanUtil.h>
#include <vulkanbase/VulkanBase.h>


Shader3D::Shader3D(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
: m_VertexShaderFile{ vertexShaderFile },
m_FragmentShaderFile{ fragmentShaderFile }
{
	createVertexShaderInfo();
	createFragmentShaderInfo();

	m_vertexInputBindingDescription = Vertex3D::GetBindingDescription();
	m_AttributeDescriptors = Vertex3D::GetAttributeDescriptions();
}

Shader3D::~Shader3D()
{
	vkDestroyShaderModule(Globals::device(), m_VertexInfo.module, nullptr);
	vkDestroyShaderModule(Globals::device(), m_FragmentInfo.module, nullptr);
}

VkPipelineShaderStageCreateInfo Shader3D::createFragmentShaderInfo() {
	std::vector<char> fragShaderCode = readFile(m_FragmentShaderFile);
	VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";
	m_FragmentInfo = fragShaderStageInfo;
	return fragShaderStageInfo;
}

VkPipelineShaderStageCreateInfo Shader3D::createVertexShaderInfo() {
	std::vector<char> vertShaderCode = readFile(m_VertexShaderFile);
	VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";
	m_VertexInfo = vertShaderStageInfo;
	return vertShaderStageInfo;
}

VkPipelineVertexInputStateCreateInfo Shader3D::createVertexInputStateInfo()
{
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_AttributeDescriptors.size());
	vertexInputInfo.pVertexBindingDescriptions = &m_vertexInputBindingDescription;
	vertexInputInfo.pVertexAttributeDescriptions = m_AttributeDescriptors.data();

	return vertexInputInfo;
}

VkPipelineInputAssemblyStateCreateInfo Shader3D::createInputAssemblyStateInfo()
{
	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssembly.primitiveRestartEnable = VK_FALSE;
	return inputAssembly;
}

VkShaderModule Shader3D::createShaderModule(const std::vector<char>& code) {
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(Globals::device(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}

	return shaderModule;
}

