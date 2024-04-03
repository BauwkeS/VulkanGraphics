#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>

class Scene
{
public:
	Scene(VkDevice device, VkPhysicalDevice physicalDevice,Pipeline* pipeline, VkRenderPass renderPass
		//,Command* commandInfo, Shader* gradientShaderInfo
	) :
		m_Device{ device },
		m_PhysicalDevice{physicalDevice},
		m_pipeline{pipeline},
		m_RenderPass{ renderPass }
		//,m_commandInfo{commandInfo},
		//m_gradientShaderInfo{gradientShaderInfo}
		{}
	~Scene() {}

	void InitItems(VkFormat swapChainImageFormat, VkExtent2D swapChainExtent,
		std::vector<VkImageView> swapChainImageViews,
		uint32_t queueFamilyIndicesGraphicsFamValue);
	void MakeMeshes();
	void PipelineDraw(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex);
	void CleanupItems();

private:
	//Shader* m_gradientShaderInfo;
	VkDevice m_Device{};
	VkPhysicalDevice m_PhysicalDevice{};
	Pipeline* m_pipeline;
	VkRenderPass m_RenderPass{};
	std::vector<MeshFactory> m_meshes{};
	//Command* m_commandInfo;
};

//Create a class that can contain multiple of theses meshes.
// For now, there is just one graphics pipeline and one shader and all meshes
// use the same shader, but that will change in the future.
// How will you create  the link between a mesh, a shader and a graphics pipeline.