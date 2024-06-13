#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <Command.h>
#include <Shader.h>

#include "Globals.h"

class Pipeline
{
private:
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader* m_GradientShaderInfo;
	VkRenderPass m_RenderPass;

	void DrawScene(VkCommandBuffer commandBuf, std::vector<MeshFactory> m_Meshes);

public:
	Pipeline(VkRenderPass renderPass)
		:
		m_RenderPass{ renderPass }
	{
		m_GradientShaderInfo = new Shader{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv"
		};
	}
	~Pipeline() {
		vkDestroyPipeline(Globals::device(), m_graphicsPipeline, nullptr);
		vkDestroyPipelineLayout(Globals::device(), m_pipelineLayout, nullptr);
	}
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer,std::vector<MeshFactory> meshes);
};
