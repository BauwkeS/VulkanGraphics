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
	//std::vector<VkFramebuffer> m_swapChainFramebuffers;
	//VkPipelineLayout m_pipelineLayout;
	//VkPipeline m_graphicsPipeline;
	//VkRenderPass m_renderPass;
	//Command* m_commandInfo;

	VkDevice m_Device;
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader* m_GradientShaderInfo;
	VkRenderPass m_RenderPass;

	std::vector<MeshFactory> m_Meshes;  // NOTE: this should go in scene

	void DrawScene(VkCommandBuffer commandBuf);

public:
	/*Pipeline(Command* commandInfo, Shader* gradientShaderInfo)
		: m_commandInfo{ commandInfo },
		m_gradientShaderInfo{gradientShaderInfo},
		m_pipelineLayout{},
		m_graphicsPipeline{} {};*/
	Pipeline(VkDevice device, VkRenderPass renderPass)
		: m_Device{ device },
		m_RenderPass{ renderPass }
	{
		//CreateGraphicsPipeline(device);
		m_GradientShaderInfo = new Shader{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv",
		m_Device
		};
	}
	~Pipeline()=default;

	void InitMesh(MeshFactory mesh);

	/*void DrawItems(VkCommandBuffer commandBuf, const VkExtent2D& swapChainExtent,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex);*/

	/*void InitShader(VkDevice device){ m_gradientShaderInfo->Initialize(device); }
	void InitCommandPool(uint32_t queueFamilyIndicesGraphicsFamValue,
		VkDevice device) {
		m_commandInfo->CreateCommandPool(queueFamilyIndicesGraphicsFamValue, device);
	}
	void InitCommandBuffer(VkDevice device){ m_commandInfo->CreateCommandBuffer(device); }*/

	//void CreateFrameBuffers(std::vector<VkImageView> swapChainImageViews,
	//	VkExtent2D swapChainExtent, VkDevice device);
	//void CreateRenderPass(VkFormat swapChainImageFormat, VkDevice device);
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex);
	/*void DrawFrameW6(uint32_t currentFrame, uint32_t imageIndex,
		VkExtent2D swapChainExtent, std::vector<MeshFactory> meshes);*/

	void DestroyPipeline();
};
