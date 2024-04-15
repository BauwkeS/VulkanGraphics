#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <Command.h>
#include <Shader.h>

class Pipeline
{
private:
	VkDevice m_Device;
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader* m_GradientShaderInfo;
	VkRenderPass m_RenderPass;

	void DrawScene(VkCommandBuffer commandBuf, std::vector<MeshFactory> m_Meshes);

public:
	Pipeline(VkDevice device, VkRenderPass renderPass)
		: m_Device{ device },
		m_RenderPass{ renderPass }
	{
		m_GradientShaderInfo = new Shader{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv",
		m_Device
		};
	}
	~Pipeline() {
		vkDestroyPipeline(m_Device, m_graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(m_Device, m_pipelineLayout, nullptr);
	}
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex,
		std::vector<MeshFactory> meshes);
};
