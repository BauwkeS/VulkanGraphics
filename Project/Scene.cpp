#include "Scene.h"

void Scene::InitItems(VkDevice device, VkPhysicalDevice physicalDevice,
	VkFormat swapChainImageFormat, VkExtent2D swapChainExtent,
	std::vector<VkImageView> swapChainImageViews,
	uint32_t queueFamilyIndicesGraphicsFamValue)
{
	// week 03
	m_pipeline->InitShader(device);
	m_pipeline->CreateRenderPass(swapChainImageFormat, device);
	m_pipeline->CreateGraphicsPipeline(device);
	m_pipeline->CreateFrameBuffers(swapChainImageViews, swapChainExtent, device);

	// week 02
	m_pipeline->InitCommandPool(queueFamilyIndicesGraphicsFamValue, device);
	//m_CommandPoolBuffer.CreateVertexBuffer(device,physicalDevice);
	m_MeshFactory.CreateVertexBuffer(device, physicalDevice);
	m_pipeline->InitCommandBuffer(device);
}

void Scene::PipelineDraw(uint32_t currentFrame, uint32_t imageIndex, VkExtent2D swapChainExtent)
{
	m_pipeline->DrawFrameW6(currentFrame, imageIndex, swapChainExtent, m_MeshFactory);
}

void Scene::CleanupItems(VkDevice device)
{
	m_MeshFactory.DestroyMesh(device);

	m_pipeline->DestroyPipeline(device);
}
