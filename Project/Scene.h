#pragma once

#include <vector>
#include <string>
#include <array>
#include <MeshFactory.h>
#include <Pipeline.h>

class Scene
{
public:
	Scene(VkDevice device, VkPhysicalDevice physicalDevice,Pipeline* pipeline, VkRenderPass renderPass
	) :
		m_Device{ device },
		m_PhysicalDevice{physicalDevice},
		m_pipeline{pipeline},
		m_RenderPass{ renderPass }
		{
		MakeMeshes();
	}
	~Scene() {
		for (auto& mesh : m_meshes) {
			mesh.DestroyMesh();
		}
	}

	void InitItems(VkFormat swapChainImageFormat, VkExtent2D swapChainExtent,
		std::vector<VkImageView> swapChainImageViews,
		uint32_t queueFamilyIndicesGraphicsFamValue);
	void MakeMeshes();
	void PipelineDraw(VkCommandBuffer commandBuffer, const VkExtent2D& swapChainExtent,
		const std::vector<VkFramebuffer>& swapChainFramebuffers, uint32_t imageIndex);
	//void CleanupItems();

private:
	VkDevice m_Device{};
	VkPhysicalDevice m_PhysicalDevice{};
	Pipeline* m_pipeline;
	VkRenderPass m_RenderPass{};
	std::vector<MeshFactory> m_meshes{};
	MeshFactory mesh{ m_Device, m_PhysicalDevice };
	MeshFactory mesh2{ m_Device, m_PhysicalDevice };
};