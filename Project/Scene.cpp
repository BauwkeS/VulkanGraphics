#include "Scene.h"

void Scene::InitItems(VkFormat swapChainImageFormat, VkExtent2D swapChainExtent,
	std::vector<VkImageView> swapChainImageViews,
	uint32_t queueFamilyIndicesGraphicsFamValue)
{
	m_pipeline->CreateGraphicsPipeline();
}

void Scene::MakeMeshes()
{
	mesh.CreateQuad(0.5f, 0.2f, 0.5f, 0.7f);
	mesh.CreateVertexBuffer();
	mesh2.CreateOval(0.0f, 0.0f, 0.2f, 100.0f);
	mesh2.CreateVertexBuffer();
	
	m_meshes.push_back(mesh);
	m_meshes.push_back(mesh2);
}

void Scene::PipelineDraw(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
	const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex)
{
	m_pipeline->DrawFrame(commandBuffer, swapChainExtent,
		swapChainFramebuffers, imageIndex, m_meshes);
}

//void Scene::CleanupItems()
//{
//	//m_MeshFactory.DestroyMesh(device);
//	for (auto& mesh : m_meshes) {
//		mesh.DestroyMesh(m_Device);
//	}
//
//	//m_pipeline->DestroyPipeline();
//}
