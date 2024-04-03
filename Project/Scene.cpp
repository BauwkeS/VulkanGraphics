#include "Scene.h"

void Scene::InitItems(VkDevice device, VkPhysicalDevice physicalDevice,
	VkFormat swapChainImageFormat, VkExtent2D swapChainExtent,
	std::vector<VkImageView> swapChainImageViews,
	uint32_t queueFamilyIndicesGraphicsFamValue)
{

	m_pipeline = new Pipeline(m_RenderPass);

	MakeMeshes(device,physicalDevice);
	m_pipeline->CreateGraphicsPipeline(device);
	//m_MeshFactory2.CreateOval(0.0f, 0.0f, 0.2f, 100.0f);

	// week 03
	//m_pipeline->CreateRenderPass(swapChainImageFormat, device);
	//m_pipeline->InitShader(device);
	//m_pipeline->CreateGraphicsPipeline(device);
	//m_pipeline->CreateFrameBuffers(swapChainImageViews, swapChainExtent, device);

	//// week 02
	//m_pipeline->InitCommandPool(queueFamilyIndicesGraphicsFamValue, device);
	////m_CommandPoolBuffer.CreateVertexBuffer(device,physicalDevice);
	//
	//for (auto& mesh : m_meshes) {
	//	mesh.CreateVertexBuffer(device, physicalDevice);
	//}


	//m_pipeline->InitCommandBuffer(device);
}

void Scene::MakeMeshes(VkDevice device, VkPhysicalDevice physicalDevice)
{
	//MeshFactory::CreateQuad(0.5f, 0.2f, 0.5f, 0.7f)
	MeshFactory mesh{ };
	mesh.CreateQuad(0.5f, 0.2f, 0.5f, 0.7f);
	mesh.CreateVertexBuffer(device, physicalDevice);
	MeshFactory mesh2{ };
	mesh2.CreateOval(0.0f, 0.0f, 0.2f, 100.0f);
	mesh2.CreateVertexBuffer(device, physicalDevice);
	
	m_meshes.push_back(mesh);
	m_meshes.push_back(mesh2);

	m_pipeline->InitMesh(mesh);
	m_pipeline->InitMesh(mesh2);

}

//void Scene::PipelineDraw(uint32_t currentFrame, uint32_t imageIndex, VkExtent2D swapChainExtent)
void Scene::PipelineDraw(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
	const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex)
{
	m_pipeline->DrawFrame(commandBuffer, swapChainExtent,
		swapChainFramebuffers, imageIndex);
}

void Scene::CleanupItems(VkDevice device)
{
	//m_MeshFactory.DestroyMesh(device);
	for (auto& mesh : m_meshes) {
		mesh.DestroyMesh(device);
	}

	m_pipeline->DestroyPipeline(device);
}
