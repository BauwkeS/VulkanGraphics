#pragma once

#include <vector>
#include <string>
#include <MeshFactory.h>
#include <Pipeline.h>
#include <Pipeline3D.h>

class Scene
{
public:
	Scene();
	~Scene();

	void MakeMeshes();
	void PipelineDraw(VkCommandBuffer commandBuffer,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex,
		uint32_t currentFrame);
	void Update(uint32_t currentFrame);

private:
	//pipeline 2D
	Pipeline* m_pipeline;
	std::vector<MeshFactory> m_meshes{};
	MeshFactory mesh{  };
	MeshFactory mesh2{  };

	//pipeline 3D
	Pipeline3D* m_pipeline2;

	//materials and textures for the PBR
	void AddTexture(const std::string& id, const std::string& path);
	void AddMaterial(const std::string& id, const std::vector<const Texture*>& textures);

	std::unordered_map<std::string, std::unique_ptr<Texture>> m_Textures;
	std::unordered_map<std::string, std::unique_ptr<Material>> m_Materials;

};