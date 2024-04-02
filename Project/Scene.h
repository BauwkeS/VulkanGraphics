#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>
#include <vulkanbase/VulkanBase.h>

//struct QueueFamilyIndices {
//	std::optional<uint32_t> graphicsFamily;
//	std::optional<uint32_t> presentFamily;
//
//	bool isComplete() {
//		return graphicsFamily.has_value() && presentFamily.has_value();
//	}
//};

class Scene
{
public:
	Scene(Pipeline* pipeline, std::vector<MeshFactory*> meshfacvec,
		Command* command, Shader* shader) :
		m_Pipeline{ pipeline },
		m_MeshFactoryVector{meshfacvec},
		m_commandInfo{command},
		m_gradientShaderInfo{shader}
	{
		
	}

	void Initialize(VkDevice device, VkFormat swapChainImageFormat,
		VkExtent2D swapChainExtent, std::vector<VkImageView> swapChainImageViews,
		VkSurfaceKHR surface, VkPhysicalDevice physicalDevice, uint32_t indices);
	//QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
private:
	Pipeline* m_Pipeline;
	std::vector<MeshFactory*> m_MeshFactoryVector;
	Command* m_commandInfo;
	Shader* m_gradientShaderInfo;
};

//Create a class that can contain multiple of theses meshes.
// For now, there is just one graphics pipeline and one shader and all meshes
// use the same shader, but that will change in the future.
// How will you create  the link between a mesh, a shader and a graphics pipeline.