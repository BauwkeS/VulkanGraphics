#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>

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
	~Shader() = default;
	std::vector<VkPipelineShaderStageCreateInfo>& GetShaderStages() { return m_ShaderStages; }

	void Initialize(const VkDevice& vkDevice);
	void DetroyShaderModules(const VkDevice& vkDevice);
	
	VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();
private:
	VkPipelineShaderStageCreateInfo createFragmentShaderInfo(const VkDevice& vkDevice);
	VkPipelineShaderStageCreateInfo createVertexShaderInfo(const VkDevice& vkDevice);
	VkShaderModule createShaderModule(const VkDevice& vkDevice, const std::vector<char>& code);

	std::string m_VertexShaderFile;
	std::string m_FragmentShaderFile;

	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStages;

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(const Shader&&) = delete;
	Shader& operator=(const Shader&&) = delete;
};
