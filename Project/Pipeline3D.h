#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>
#include <Command.h>
#include <Shader.h>

#include "Globals.h"
#include "Shader3D.h"
#include "Mesh3D.h"

class Pipeline3D
{
private:
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader3D* m_GradientShaderInfo;

	void DrawScene(VkCommandBuffer commandBuf, std::vector<MeshFactory> m_Meshes);

public:
	Pipeline3D()
	{
		m_GradientShaderInfo = new Shader3D{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv"
		};
	}
	~Pipeline3D();
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer,std::vector<MeshFactory> meshes);
};
