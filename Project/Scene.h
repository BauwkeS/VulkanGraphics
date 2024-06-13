#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>

class Scene
{
public:
	Scene(Pipeline* pipeline, VkRenderPass renderPass
	) :
		m_pipeline{pipeline},
		m_RenderPass{ renderPass }
		{
		m_pipeline2 = new Pipeline(renderPass);
		MakeMeshes();
	}
	~Scene() {
		for (auto& mesh : m_meshes) {
			mesh.DestroyMesh();
		}
	}

	void InitItems();
	void MakeMeshes();
	void PipelineDraw(VkCommandBuffer commandBuffer,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex);
	//void CleanupItems();

private:
	Pipeline* m_pipeline;
	Pipeline* m_pipeline2;
	VkRenderPass m_RenderPass{};
	std::vector<MeshFactory> m_meshes{};
	std::vector<MeshFactory> m_meshes2{};
	MeshFactory mesh{  };
	MeshFactory mesh2{  };
	MeshFactory mesh3{  };
};