#include "Scene.h"
#include "Globals.h"

Scene::Scene()
{
	m_pipeline = new Pipeline();
	m_pipeline2 = new Pipeline3D();
	MakeMeshes();
}

Scene::~Scene()
{
	for (auto& mesh : m_meshes) {
		mesh.DestroyMesh();
	}
	vkDestroyRenderPass(Globals::device(), Globals::renderPass(), nullptr);
}

void Scene::MakeMeshes()
{
	//pipeline 2D
	mesh.CreateQuad(0.5f, 0.2f, 0.5f, 0.7f);
	mesh.CreateVertexBuffer();
	mesh2.CreateOval(0.0f, 0.0f, 0.2f, 100.0f);
	mesh2.CreateVertexBuffer();

	m_meshes.push_back(mesh);
	m_meshes.push_back(mesh2);

	//pipeline 3D

	//Add cube info inside pipeline
	AddTexture("cube_albedo", "Textures/cube/cube_albedo.jpg");
	AddTexture("cube_ao", "Textures/cube/cube_ao.jpg");
	AddTexture("cube_normal", "Textures/cube/cube_normal.jpg");
	AddTexture("cube_roughness", "Textures/cube/cube_roughness.jpg");
	AddTexture("cube_metal", "Textures/cube/cube_metal.jpg");

	std::vector<const Texture*> cubeTextures{
		m_Textures["cube_albedo"].get(),
			m_Textures["cube_normal"].get(),
			m_Textures["cube_ao"].get(),
			m_Textures["cube_roughness"].get(),
			m_Textures["cube_metal"].get() };

	AddMaterial("cube",cubeTextures);

	m_pipeline2->AddMesh("Models/cube.obj", m_Materials["cube"].get(), glm::vec3(-1, 0, 4));

	//sphere
	AddTexture("sphere_albedo", "Textures/sphere/sphere_albedo.jpg");
	AddTexture("sphere_ao", "Textures/sphere/sphere_ao.jpg");
	AddTexture("sphere_normal", "Textures/sphere/sphere_normal.jpg");
	AddTexture("sphere_roughness", "Textures/sphere/sphere_roughness.jpg");
	AddTexture("sphere_metal", "Textures/sphere/sphere_metal.png");

	std::vector<const Texture*> sphereTextures{
		m_Textures["sphere_albedo"].get(),
			m_Textures["sphere_normal"].get(),
			m_Textures["sphere_ao"].get(),
			m_Textures["sphere_metal"].get(),
			m_Textures["sphere_roughness"].get() };

	AddMaterial("sphere", sphereTextures);

	m_pipeline2->AddMesh("Models/sphere.obj", m_Materials["sphere"].get(), glm::vec3(1,0,4));
}

void Scene::PipelineDraw(VkCommandBuffer commandBuffer,
	const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex, uint32_t currentFrame)
{
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

	m_pipeline->DrawFrame(commandBuffer,m_meshes);
	m_pipeline2->DrawFrame(commandBuffer,currentFrame);

	vkCmdEndRenderPass(commandBuffer);  
}

void Scene::Update(uint32_t currentFrame)
{
	m_pipeline2->Update(currentFrame);
}

void Scene::AddTexture(const std::string& id, const std::string& path)
{
	m_Textures[id] = std::make_unique<Texture>(path);
}

void Scene::AddMaterial(const std::string& id, const std::vector<const Texture*>& textures)
{
	m_Materials[id] = std::make_unique<Material>(textures);
}