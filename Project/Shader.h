#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>

class Shader
{
public:
	Shader(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile, VkDevice device
		) : m_VertexShaderFile{ vertexShaderFile },
		m_FragmentShaderFile{ fragmentShaderFile },
		m_Device{device}
	{
	}
	~Shader() {
		vkDestroyShaderModule(m_Device, m_VertexInfo.module, nullptr);
		vkDestroyShaderModule(m_Device, m_FragmentInfo.module, nullptr);
	}
	
	void Initialize();
	//void DetroyShaderModules();
	
	VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
	
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();
	VkPipelineShaderStageCreateInfo createFragmentShaderInfo();
	VkPipelineShaderStageCreateInfo createVertexShaderInfo();
private:
	VkShaderModule createShaderModule(const std::vector<char>& code);

	std::string m_VertexShaderFile;
	std::string m_FragmentShaderFile;
	VkDevice m_Device{};

	VkPipelineShaderStageCreateInfo m_VertexInfo{}, m_FragmentInfo{};

	std::array<VkVertexInputAttributeDescription, 2> m_AttributeDescriptors{};
	VkVertexInputBindingDescription m_vertexInputBindingDescription{};

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(const Shader&&) = delete;
	Shader& operator=(const Shader&&) = delete;
};
