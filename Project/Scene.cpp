#include "Scene.h"
#include "Globals.h"

Scene::Scene()
{
	m_pipeline = new Pipeline(Globals::renderPass());
	m_pipeline2 = new Pipeline(Globals::renderPass());
	MakeMeshes();
}

Scene::~Scene()
{
	for (auto& mesh : m_meshes) {
		mesh.DestroyMesh();
	}
	vkDestroyRenderPass(Globals::device(), Globals::renderPass(), nullptr);
}

void Scene::InitItems()
{
	m_pipeline->CreateGraphicsPipeline();
	m_pipeline2->CreateGraphicsPipeline();
}

void Scene::MakeMeshes()
{
	mesh.CreateQuad(0.5f, 0.2f, 0.5f, 0.7f);
	mesh.CreateVertexBuffer();
	mesh2.CreateOval(0.0f, 0.0f, 0.2f, 100.0f);
	mesh2.CreateVertexBuffer();

	mesh3.CreateQuad(-0.2f, -0.7f, 0.2f, 0.5f);
	mesh3.CreateVertexBuffer();
	
	m_meshes.push_back(mesh);
	m_meshes.push_back(mesh2);
	m_meshes2.push_back(mesh3);
}

void Scene::PipelineDraw(VkCommandBuffer commandBuffer,
	const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex)
{
	/*std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = {
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	clearValues[1].depthStencil = { 1.0f, 0 };*/



	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = Globals::renderPass();
	renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = Globals::swapChainExtent();

	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	m_pipeline->DrawFrame(commandBuffer,m_meshes);
	m_pipeline2->DrawFrame(commandBuffer,m_meshes2);

	vkCmdEndRenderPass(commandBuffer);
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
