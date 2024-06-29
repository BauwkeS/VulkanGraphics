#include "Scene.h"
#include "Globals.h"

Scene::Scene()
{
	m_pipeline = new Pipeline();
	m_pipeline2 = new Pipeline3D();
	MakeMeshes();
	m_pipeline2->CreateUBODescriptorSets();
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
	//m_pipeline2->CreateGraphicsPipeline();
}

void Scene::MakeMeshes()
{
	mesh.CreateQuad(0.5f, 0.2f, 0.5f, 0.7f);
	mesh.CreateVertexBuffer();
	mesh2.CreateOval(0.0f, 0.0f, 0.2f, 100.0f);
	mesh2.CreateVertexBuffer();

	m_meshes.push_back(mesh);
	m_meshes.push_back(mesh2);

	//mesh3d_1 = new Mesh3D("Models/viking_room.obj");
	m_pipeline2->AddMesh("Models/viking_room.obj", "Textures/viking_room.png");
}

void Scene::PipelineDraw(VkCommandBuffer commandBuffer,
	const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex, uint32_t currentFrame)
{
	/*std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = {
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	clearValues[1].depthStencil = { 1.0f, 0 };*/

	//m_pipeline2->UpdateUBO(currentFrame);

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = Globals::renderPass();
	renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex];
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = Globals::swapChainExtent();

	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = {
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	clearValues[1].depthStencil = { 1.0f, 0 };
	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	renderPassInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

	//m_pipeline->DrawFrame(commandBuffer,m_meshes);
	m_pipeline2->DrawFrame(commandBuffer,currentFrame);

	vkCmdEndRenderPass(commandBuffer);
}

void Scene::Update(uint32_t currentFrame)
{
	m_pipeline2->UpdateUBO(currentFrame);
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
