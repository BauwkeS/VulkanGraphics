#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <Command.h>
#include <Shader.h>

#include "MeshFactory.h"

class Pipeline
{
private:
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader* m_GradientShaderInfo;

	void DrawScene(VkCommandBuffer commandBuf, std::vector<MeshFactory> m_Meshes);

public:
	Pipeline()
	{
		m_GradientShaderInfo = new Shader{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv"
		};
	}
	~Pipeline();
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer,std::vector<MeshFactory> meshes);
};
