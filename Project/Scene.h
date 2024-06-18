#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>
#include <Pipeline3D.h>

class Scene
{
public:
	Scene();
	~Scene();

	void InitItems();
	void MakeMeshes();
	void PipelineDraw(VkCommandBuffer commandBuffer,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex,
		uint32_t currentFrame);
	//void CleanupItems();
	void Update(uint32_t currentFrame);
private:
	Pipeline* m_pipeline;
	Pipeline3D* m_pipeline2;
	std::vector<MeshFactory> m_meshes{};
	MeshFactory mesh{  };
	MeshFactory mesh2{  };
};