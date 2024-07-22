#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <array>

#include "Globals.h"
#include "Shader3D.h"
#include "Mesh3D.h"

class Pipeline3D
{

public:
	void CreateUBODescriptorSets(const std::vector<const Texture*>& textures);
private:
	VkPipeline m_graphicsPipeline{};
	VkPipelineLayout m_pipelineLayout{};

	Shader3D* m_GradientShaderInfo;

	void DrawScene(VkCommandBuffer commandBuf);

	std::vector<std::unique_ptr<Mesh3D>> m_Meshes;

	//ubo stuff
	void CreateUBOBuffers();
	
	std::vector<std::unique_ptr<Buffer>> m_UBOBuffers;
	std::vector<void*> m_UBOBuffersMapped{};
	std::vector<VkDescriptorSet> m_UBODescriptorSets{};
	std::vector<VkDescriptorSet> m_MaterialDescriptorSets{};

	void CreateTextureDescriptorSet();
	//VkDescriptorSet m_TextureDescriptorSets{};

	/*std::unordered_map<std::string, std::unique_ptr<Material>> m_Materials;*/

public:
	Pipeline3D();
	~Pipeline3D();
	void CreateGraphicsPipeline();

	void DrawFrame(VkCommandBuffer commandBuffer, uint32_t currentFrame);

	Mesh3D* AddMesh(const std::string& modelPath, const Material* materialPtr);
	//Mesh3D* AddMesh(const std::string& modelPath, const std::string& id);
	/*void AddTexture(const std::string& id, const std::string& path);
	void AddMaterial(const std::string& id,
		const std::vector<const Texture*>& textures);
	std::unordered_map<std::string, std::unique_ptr<Texture>> m_Textures;*/

	void UpdateUBO(uint32_t currentFrame);

	void Update(uint32_t currentFrame);
};
