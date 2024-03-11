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
	std::vector<VkFramebuffer> m_swapChainFramebuffers;
	VkPipelineLayout m_pipelineLayout;
	VkPipeline m_graphicsPipeline;
	VkRenderPass m_renderPass;
	Command* m_commandInfo;
	Shader* m_gradientShaderInfo;

public:
	Pipeline(Command* commandInfo, Shader* gradientShaderInfo)
		: m_commandInfo{ commandInfo },
		m_gradientShaderInfo{gradientShaderInfo},
		m_pipelineLayout{},
		m_graphicsPipeline{},
		m_renderPass{} {};
	~Pipeline()=default;

	void CreateFrameBuffers(std::vector<VkImageView> swapChainImageViews,
		VkExtent2D swapChainExtent, VkDevice device);
	void CreateRenderPass(VkFormat swapChainImageFormat, VkDevice device);
	void CreateGraphicsPipeline(VkDevice device);

	void DrawFrame(uint32_t imageIndex, VkExtent2D swapChainExtent,
		uint32_t currentFrame);
	void DrawFrameW6(uint32_t currentFrame, uint32_t imageIndex,
		VkExtent2D swapChainExtent);

	void DestroyPipeline(VkDevice device);
};
