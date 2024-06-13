#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>

class Scene
{
public:
	Scene();
	~Scene();

	void InitItems();
	void MakeMeshes();
	void PipelineDraw(VkCommandBuffer commandBuffer,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex);
	//void CleanupItems();

private:
	Pipeline* m_pipeline;
	Pipeline* m_pipeline2;
	std::vector<MeshFactory> m_meshes{};
	std::vector<MeshFactory> m_meshes2{};
	MeshFactory mesh{  };
	MeshFactory mesh2{  };
	MeshFactory mesh3{  };
};