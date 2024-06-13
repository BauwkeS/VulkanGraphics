#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <memory>

#include "Vertex.h"
#include "Buffer.h"

class Shader3D
{
public:
	Shader3D(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile
		) : m_VertexShaderFile{ vertexShaderFile },
		m_FragmentShaderFile{ fragmentShaderFile }
	{
	}
	~Shader3D();
	
	void Initialize();
	//void DetroyShaderModules();

	VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
	
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();
	VkPipelineShaderStageCreateInfo createFragmentShaderInfo();
	VkPipelineShaderStageCreateInfo createVertexShaderInfo();

	//ubo stuff
	void CreateDescriptorSetLayout();
	const VkDescriptorSetLayout& GetDescriptorSetLayout() { return m_DescriptorSetLayout; }
	void BindDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index);

private:
	VkShaderModule createShaderModule(const std::vector<char>& code);

	std::string m_VertexShaderFile;
	std::string m_FragmentShaderFile;

	VkPipelineShaderStageCreateInfo m_VertexInfo{}, m_FragmentInfo{};

	std::array<VkVertexInputAttributeDescription, 2> m_AttributeDescriptors{};
	VkVertexInputBindingDescription m_vertexInputBindingDescription{};

	//ubo stuff
	VkDescriptorSetLayout m_DescriptorSetLayout;
	std::unique_ptr<Buffer> m_UBOBuffer;
	VertexUBO m_UBOSrc;
	//command pool here in Koen's version

	//--


	Shader3D(const Shader3D&) = delete;
	Shader3D& operator=(const Shader3D&) = delete;
	Shader3D(const Shader3D&&) = delete;
	Shader3D& operator=(const Shader3D&&) = delete;
};
