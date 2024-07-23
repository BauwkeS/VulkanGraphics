#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>

//#include <MeshFactory.h>

class Command
{
public:

	Command();
	~Command();
	operator VkCommandBuffer() const { return m_Buffer; }

	void CreateCommandBuffer();

	void DestroyCommandPool(std::vector<VkFramebuffer> swapChainFramebuffers);

	VkCommandBuffer GetBuffer() { return m_Buffer; }

	void BufferStart();
	void BufferEnd();
	void BufferSubmit();

private:
	VkCommandBuffer m_Buffer{};
};
