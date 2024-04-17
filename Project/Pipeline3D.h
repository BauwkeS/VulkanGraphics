#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <Command.h>
#include <Shader.h>

#include "UniformBuffer.h"

class Pipeline3D
{
private:
	VkDevice m_Device;
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader* m_GradientShaderInfo;
	VkRenderPass m_RenderPass;
	UniformBuffer* m_UniformBuffer;

	VkDescriptorSetLayout m_DescriptorSetLayout;
	VkPipelineLayout m_PipelineLayout;

	void createDescriptorSetLayout();

	void DrawScene(VkCommandBuffer commandBuf, std::vector<MeshFactory> m_Meshes);

public:
	Pipeline3D(VkDevice device, VkRenderPass renderPass, UniformBuffer* uniformBuffer)
		: m_Device{ device },
		m_RenderPass{ renderPass },
	m_UniformBuffer{uniformBuffer}
	{
		createDescriptorSetLayout();
		m_GradientShaderInfo = new Shader{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv",
		m_Device
		};
	}
	~Pipeline3D() {
		vkDestroyPipeline(m_Device, m_graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(m_Device, m_pipelineLayout, nullptr);
		vkDestroyDescriptorSetLayout(m_Device, m_DescriptorSetLayout, nullptr);
	}
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex,
		std::vector<MeshFactory> meshes);
};
