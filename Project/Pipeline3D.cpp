#include "Pipeline3D.h"
#include "Globals.h"
#include "Vertex.h"
#include <stdexcept>

#include "Camera.h"

void Pipeline3D::CreateUBOBuffers()
{
	//create and map ubo
	m_UBOBuffers.resize(Globals::MAX_FRAMES_IN_FLIGHT);
	m_UBOBuffersMapped.resize(Globals::MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < Globals::MAX_FRAMES_IN_FLIGHT; i++)
	{
		m_UBOBuffers[i] = std::make_unique<Buffer>(
			sizeof(VertexUBO),
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		vkMapMemory(Globals::device(),
			m_UBOBuffers[i]->GetBufferMemory(),
			0,
			sizeof(VertexUBO),
			0,
			&m_UBOBuffersMapped[i]);
	}
}

void Pipeline3D::CreateUBODescriptorSets()
{
	//update ubo descriptor sets
	const std::vector<VkDescriptorSetLayout> layouts(
		Globals::MAX_FRAMES_IN_FLIGHT,
		Globals::UBODescriptorSetLayout());

	VkDescriptorSetAllocateInfo allocateInfo{};
	allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocateInfo.descriptorPool = Globals::descriptorPool();
	allocateInfo.descriptorSetCount
		= static_cast<uint32_t>(Globals::MAX_FRAMES_IN_FLIGHT);
	allocateInfo.pSetLayouts = layouts.data();

	m_UBODescriptorSets.resize(Globals::MAX_FRAMES_IN_FLIGHT);
	if (vkAllocateDescriptorSets(Globals::device(),
		&allocateInfo,
		m_UBODescriptorSets.data())
		!= VK_SUCCESS)
	{
		throw std::runtime_error("Failed to allocate descriptor sets");
	}

	for (size_t i = 0; i < Globals::MAX_FRAMES_IN_FLIGHT; i++)
	{
		VkDescriptorBufferInfo bufferInfo{};
		bufferInfo.buffer = m_UBOBuffers[i]->GetBuffer();
		bufferInfo.offset = 0;
		bufferInfo.range = sizeof(VertexUBO);

		VkWriteDescriptorSet descriptorWrite{};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = m_UBODescriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = &bufferInfo;
		descriptorWrite.pImageInfo = nullptr;
		descriptorWrite.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(Globals::device(), 1, &descriptorWrite,
			0, nullptr);
	}
}

Pipeline3D::Pipeline3D()
{
	m_GradientShaderInfo = new Shader3D{
		   "shaders/shader_ubo.vert.spv",
		   "shaders/shader_ubo.frag.spv"
	};

	CreateGraphicsPipeline();

	//ubo
	CreateUBOBuffers();
	CreateUBODescriptorSets();
	
}

Pipeline3D::~Pipeline3D()
{
	vkDestroyPipeline(Globals::device(), m_graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(Globals::device(), m_pipelineLayout, nullptr);
}

void Pipeline3D::CreateGraphicsPipeline()
{
	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.scissorCount = 1;

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.pSampleMask = nullptr;
	multisampling.alphaToCoverageEnable = VK_FALSE;
	multisampling.alphaToOneEnable = VK_FALSE;

	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.stencilTestEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	std::vector<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();

	VkDescriptorSetLayout setLayouts[]{
		Globals::UBODescriptorSetLayout(),
		Globals::TextureDescriptorSetLayout()
	};

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 2;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pSetLayouts = setLayouts;

	if (vkCreatePipelineLayout(Globals::device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

	VkGraphicsPipelineCreateInfo pipelineInfo{};

	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

	auto vertexShaderStageInfo = m_GradientShaderInfo->createVertexShaderInfo();
	auto fragmentShaderStageInfo = m_GradientShaderInfo->createFragmentShaderInfo();
	VkPipelineShaderStageCreateInfo shaderStages[] = { vertexShaderStageInfo,
														   fragmentShaderStageInfo };


	auto vertexInputStateInfo = m_GradientShaderInfo->createVertexInputStateInfo();
	auto inputAssemblyStateInfo = m_GradientShaderInfo->createInputAssemblyStateInfo();

	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputStateInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemblyStateInfo;

	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = Globals::renderPass();
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if (vkCreateGraphicsPipelines(Globals::device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}
}

void Pipeline3D::DrawFrame(VkCommandBuffer commandBuffer, uint32_t currentFrame)
{
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)Globals::swapChainExtent().width;
	viewport.height = (float)Globals::swapChainExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = Globals::swapChainExtent();
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	vkCmdBindDescriptorSets(commandBuffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		m_pipelineLayout,
		0,
		1,
		&m_UBODescriptorSets[currentFrame],
		0,
		nullptr);

	for (auto&& mesh : m_Meshes) {

		VkDescriptorSet materialDescriptorSet = mesh->GetMaterialDescriptorSet();
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			m_pipelineLayout,
			1,
			1,
			&materialDescriptorSet,
			0,
			nullptr);

		mesh->Draw(commandBuffer);
	}
	
}

Mesh3D* Pipeline3D::AddMesh(const std::string& modelPath , const Material* materialPtr, glm::vec3 addToPos)
{
	m_Meshes.emplace_back(std::make_unique<Mesh3D>(modelPath, materialPtr, addToPos));
	return m_Meshes.back().get();
}

void Pipeline3D::UpdateUBO(uint32_t currentFrame)
{
	VertexUBO ubo{};
	ubo.view = Globals::camera()->View();
	ubo.proj = Globals::camera()->Proj();
	ubo.model = glm::mat4(1.0f);
	ubo.proj[1][1] *= -1;

	memcpy(m_UBOBuffersMapped[currentFrame], &ubo, sizeof(ubo));
}

void Pipeline3D::Update(uint32_t currentFrame)
{
	//Update UBO
	UpdateUBO(currentFrame);

	//Update meshes
	for (auto&& mesh : m_Meshes)
	{
		mesh->Update();
	}
}