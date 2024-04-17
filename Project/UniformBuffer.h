#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vulkan/vulkan_core.h>
#include "vulkanbase/VulkanBase.h"

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class UniformBuffer
{
private:
    VkDevice m_Device{};

	VkBuffer m_IndexBuffer;
	VkDeviceMemory m_IndexBufferMemory;

	std::vector<VkBuffer> m_UniformBuffers;
	std::vector<VkDeviceMemory> m_UniformBuffersMemory;
	std::vector<void*> m_UniformBuffersMapped;
	
public:
	UniformBuffer(
		VkDevice device
	) : m_Device{ device }
	{
	}
	~UniformBuffer();

	void CreateUniformBuffers();
};
