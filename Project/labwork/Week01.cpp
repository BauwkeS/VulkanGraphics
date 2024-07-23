#include "vulkanbase/VulkanBase.h"
#include "Globals.h"

void VulkanBase::CreateDescriptorPool()
{
	constexpr int maxTexture{ 50 };

	std::array<VkDescriptorPoolSize, 3> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount
		= static_cast<uint32_t>(Globals::MAX_FRAMES_IN_FLIGHT);

	poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[1].descriptorCount
		= static_cast<uint32_t>(Globals::MAX_FRAMES_IN_FLIGHT);

	poolSizes[2].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[2].descriptorCount = maxTexture;

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(Globals::MAX_FRAMES_IN_FLIGHT) * 2
		+ maxTexture;

	if (vkCreateDescriptorPool(Globals::device(), &poolInfo, nullptr, &m_DescriptorPool)
		!= VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create descriptor pool");
	}
	Globals::s_DescriptorPool = m_DescriptorPool;
}

void VulkanBase::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "BauwkeSpooren", nullptr, nullptr);


	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window,
		[](GLFWwindow*, int key, int, int action, int) -> void
		{
			if (action == GLFW_PRESS)
			{
				InputSys::OnKeyDown(key);
			}
			else if (action == GLFW_RELEASE)
			{
				InputSys::OnKeyUp(key);
			}
		});
	glfwSetCursorPosCallback(window,
		[](GLFWwindow*, double xPos, double yPos) -> void
		{
			InputSys::OnMouseMove({ xPos, yPos });
		});
	glfwSetMouseButtonCallback(window,
		[](GLFWwindow*, int button, int action, int)
		{
			if (action == GLFW_PRESS)
			{
				InputSys::OnButtonDown(button);
			}
			else if (action == GLFW_RELEASE)
			{
				InputSys::OnButtonUp(button);
			}
		});

	glfwSetFramebufferSizeCallback(
		window,
		[](GLFWwindow* windowPtr, int width, int height) -> void
		{
			const auto app
				= static_cast<VulkanBase*>(glfwGetWindowUserPointer(windowPtr));
			app->m_FrameBufferResized = true;
		});
}
