#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "VulkanUtil.h"

#include <array>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>

#include "Shader.h"
#include "Command.h"
#include "Pipeline.h"
#include "MeshFactory.h"
#include <Scene.h>
#include <labwork/Week03.cpp>

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

//const std::vector<Vertex> vertices = MeshFactory::CreateQuad(1.0f,0.0f,0.0f,1.0f);
//const std::vector<Vertex> vertices = MeshFactory::CreateRoundedQuad(0.0f, 0.0f, 0.0f, 1.0f, 0.4,32);

//const std::vector<Vertex> vertices = {
//	{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
//	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
//};

class VulkanBase {
public:

	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

private:
	void initVulkan() {
		// week 06
		createInstance();
		setupDebugMessenger();
		createSurface();

		//-------------
		// week 05
		pickPhysicalDevice();	
		createLogicalDevice();

		// week 04 
		createSwapChain();
		createImageViews();
		
		createRenderPass();

		m_Pipeline = new Pipeline(m_renderPass);
		m_SceneOne = new Scene(m_Pipeline, m_renderPass);

		m_SceneOne->InitItems();
		createFrameBuffers();

		m_CommandPoolBuffer = new Command();
		m_CommandPoolBuffer->CreateCommandPool(findQueueFamilies(physicalDevice).graphicsFamily.value());
		m_CommandPoolBuffer->CreateCommandBuffer();

		//// week 03
		//m_Pipeline.InitShader(device);
		//m_Pipeline.CreateRenderPass(swapChainImageFormat, device);
		//m_Pipeline.CreateGraphicsPipeline(device);
		//m_Pipeline.CreateFrameBuffers(swapChainImageViews, swapChainExtent, device);

		//// week 02
		//m_Pipeline.InitCommandPool(findQueueFamilies(physicalDevice).graphicsFamily.value(),device);
		////m_CommandPoolBuffer.CreateVertexBuffer(device,physicalDevice);
		//m_MeshFactory.CreateVertexBuffer(device,physicalDevice);
		//m_Pipeline.InitCommandBuffer(device);
		//-----
		// week 06
		createSyncObjects();
	}

	void mainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			// week 06

			drawFrame();
		}
		vkDeviceWaitIdle(device);
	}

	void cleanup() {
		vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
		vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
		vkDestroyFence(device, inFlightFence, nullptr);

		/*m_MeshFactory.DestroyMesh(device);

		m_Pipeline.DestroyPipeline(device);*/

		//m_SceneOne->CleanupItems();


		vkDestroyRenderPass(device, m_renderPass, nullptr);
		//m_CommandPoolBuffer.DestroyCommandPool(device, m_swapChainFramebuffers);



		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(device, imageView, nullptr);
		}

		delete m_CommandPoolBuffer;
		delete m_Pipeline;
		delete m_SceneOne;
		//eyo framebuffer is an issue here

		if (enableValidationLayers) {
			DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
		}
		vkDestroySwapchainKHR(device, swapChain, nullptr);
		vkDestroyDevice(device, nullptr);

		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void createSurface() {
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	/*Shader m_GradientShader{
		"shaders/shader.vert.spv",
		"shaders/shader.frag.spv"
	};*/
	

	uint32_t currentFrame = 0;

	// Week 01: 
	// Actual window
	// simple fragment + vertex shader creation functions
	// These 5 functions should be refactored into a separate C++ class
	// with the correct internal state.

	GLFWwindow* window;
	void initWindow();


	std::vector<VkFramebuffer> m_swapChainFramebuffers;

	VkRenderPass m_renderPass;

	// Week 04
	// Swap chain and image view support

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<VkImageView> swapChainImageViews;

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	void createSwapChain();
	void createImageViews();

	// Week 05 
	// Logical and physical device

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	
	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice();

	// Week 06
	// Main initialization

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkDevice device = VK_NULL_HANDLE;
	VkSurfaceKHR surface;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	std::vector<const char*> getRequiredExtensions();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createInstance();

	void createSyncObjects();
	void drawFrame();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
		return VK_FALSE;
	}

	Command* m_CommandPoolBuffer{};
	Pipeline* m_Pipeline{ };
	
	Scene* m_SceneOne{};
	void createRenderPass();
	void  createFrameBuffers();
};