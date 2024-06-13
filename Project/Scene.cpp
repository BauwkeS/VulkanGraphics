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
	renderPassInfo.renderPass = m_RenderPass;
	renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = Globals::swapChainExtent();

	VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	m_pipeline->DrawFrame(commandBuffer,m_meshes);

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
