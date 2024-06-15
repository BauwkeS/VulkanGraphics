#include "Pipeline3D.h"
#include "Globals.h"
#include <stdexcept>
#include <MeshFactory.h>


void Pipeline3D::DrawScene(VkCommandBuffer commandBuffer)
{
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

	/*vkCmdBindDescriptorSets(commandBuffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		m_PipelineLayout,
		0,
		1,
		&m_UniformDescriptorSets[currentFrame],
		0,
		nullptr);*/

	for (auto&& mesh : m_Meshes) {
		/*VkDescriptorSet textureDescriptorSet = sprite->GetTextureDescriptorSet();
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			m_PipelineLayout,
			1,
			1,
			&textureDescriptorSet,
			0,
			nullptr);*/
		mesh->Draw(commandBuffer);
	}
}

void Pipeline3D::CreateUBODescriptorSets()
{
}

Pipeline3D::Pipeline3D()
{
	m_GradientShaderInfo = new Shader3D{
		   "shaders/shader_ubo.vert.spv",
		   "shaders/shader_ubo.frag.spv"
	};

	CreateGraphicsPipeline();
}

Pipeline3D::~Pipeline3D()
{
	vkDestroyPipeline(Globals::device(), m_graphicsPipeline, nullptr);
	vkDestroyPipelineLayout(Globals::device(), m_pipelineLayout, nullptr);

}

void Pipeline3D::CreateGraphicsPipeline()
{
	//m_GradientShaderInfo->Initialize();

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
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

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

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pushConstantRangeCount = 0;

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

void Pipeline3D::DrawFrame(VkCommandBuffer commandBuffer)
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

	//drawScene();
	//vkCmdDraw(commandBuffer, 6, 1, 0, 0);
	DrawScene(commandBuffer);

	
}

Mesh3D* Pipeline3D::AddMesh(const std::string& modelPath /*,const std::string& texturePath*/)
{
	m_Meshes.emplace_back(std::make_unique<Mesh3D>(modelPath));
	return m_Meshes.back().get();
}

//void Pipeline::DestroyPipeline()
//{
//	vkDestroyPipeline(m_Device,m_graphicsPipeline, nullptr);
//	vkDestroyPipelineLayout(m_Device, m_pipelineLayout, nullptr);
//	//vkDestroyRenderPass(device, m_renderPass, nullptr);
//}
