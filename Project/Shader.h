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
		const std::string& fragmentShaderFile
		) : m_VertexShaderFile{ vertexShaderFile },
		m_FragmentShaderFile{ fragmentShaderFile }
	{
	}
	~Shader();
	void Initialize();
	
	VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
	
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();
	VkPipelineShaderStageCreateInfo createFragmentShaderInfo();
	VkPipelineShaderStageCreateInfo createVertexShaderInfo();
private:
	VkShaderModule createShaderModule(const std::vector<char>& code);

	std::string m_VertexShaderFile;
	std::string m_FragmentShaderFile;

	VkPipelineShaderStageCreateInfo m_VertexInfo{}, m_FragmentInfo{};

	std::array<VkVertexInputAttributeDescription, 2> m_AttributeDescriptors{};
	VkVertexInputBindingDescription m_vertexInputBindingDescription{};

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(const Shader&&) = delete;
	Shader& operator=(const Shader&&) = delete;
};
