#include "Scene.h"

void Scene::Initialize(VkDevice device, VkFormat swapChainImageFormat,
	VkExtent2D swapChainExtent, std::vector<VkImageView> swapChainImageViews,
	VkSurfaceKHR surface, VkPhysicalDevice physicalDevice, uint32_t indices)
{
	m_gradientShaderInfo->Initialize(device);
	m_Pipeline->CreateRenderPass(swapChainImageFormat, device);
	m_Pipeline->CreateGraphicsPipeline(device);
	m_Pipeline->CreateFrameBuffers(swapChainImageViews, swapChainExtent, device);

	// week 02
	m_commandInfo->CreateCommandPool(indices, device);
	//m_CommandPoolBuffer.CreateVertexBuffer(device,physicalDevice);
	for (int i = 0; i < m_MeshFactoryVector.size(); i++)
	{
		m_MeshFactoryVector[i]->CreateVertexBuffer(device, physicalDevice);
	}
	m_commandInfo->CreateCommandBuffer(device);
}

