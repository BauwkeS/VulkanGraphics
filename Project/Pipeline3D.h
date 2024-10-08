#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>

#include "Globals.h"
#include "Shader3D.h"
#include "Mesh3D.h"

class Pipeline3D
{

public:
	void CreateUBODescriptorSets();
private:
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};
	Shader3D* m_GradientShaderInfo;
	std::vector<std::unique_ptr<Mesh3D>> m_Meshes;

	//descriptor/ubo stuff
	void CreateUBOBuffers();
	void CreateTextureDescriptorSet();
	std::vector<std::unique_ptr<Buffer>> m_UBOBuffers;
	std::vector<void*> m_UBOBuffersMapped{};
	std::vector<VkDescriptorSet> m_UBODescriptorSets{};

public:
	Pipeline3D();
	~Pipeline3D();
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer, uint32_t currentFrame);
	Mesh3D* AddMesh(const std::string& modelPath, const Material* materialPtr, glm::vec3 addToPos);

	void UpdateUBO(uint32_t currentFrame);
	void Update(uint32_t currentFrame);
};
