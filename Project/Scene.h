#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>

class Scene
{
public:
	Scene(Pipeline* pipeline
		//,Command* commandInfo, Shader* gradientShaderInfo
	) :
		m_pipeline{pipeline}
		//,m_commandInfo{commandInfo},
		//m_gradientShaderInfo{gradientShaderInfo}
		{}
	~Scene() {}

	void InitItems(VkDevice device, VkPhysicalDevice physicalDevice,
		VkFormat swapChainImageFormat, VkExtent2D swapChainExtent,
		std::vector<VkImageView> swapChainImageViews,
		uint32_t queueFamilyIndicesGraphicsFamValue);
	void PipelineDraw(uint32_t currentFrame, uint32_t imageIndex,
		VkExtent2D swapChainExtent);
	void CleanupItems(VkDevice device);

private:
	Pipeline* m_pipeline;
	MeshFactory m_MeshFactory{};
	//Command* m_commandInfo;
	//Shader* m_gradientShaderInfo;
};

//Create a class that can contain multiple of theses meshes.
// For now, there is just one graphics pipeline and one shader and all meshes
// use the same shader, but that will change in the future.
// How will you create  the link between a mesh, a shader and a graphics pipeline.