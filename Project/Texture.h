#pragma once
#include <vulkan/vulkan_core.h>
#include <string>

class Texture
{
public:
    Texture(std::string texturePath);
    ~Texture();

    Texture(Texture&& other) = delete;
    Texture(const Texture& other) = delete;
    Texture operator=(Texture&& other) = delete;
    Texture operator=(const Texture& other) = delete;

    //image functions
    static VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    static void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
        VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image,
        VkDeviceMemory& imageMemory);
    static void TransitionImageLayout(VkImage image,
        VkFormat format, VkImageLayout oldLayout,
        VkImageLayout newLayout);
    static void CopyBufferToImage(VkBuffer buffer,
        VkImage image, uint32_t width,
        uint32_t height);

    //getters
    [[nodiscard]] const VkDescriptorImageInfo& GetImageInfo() const
    {
        return m_ImageInfo;
    }

    [[nodiscard]] const VkImageView GetTextureImageView() const
    {
        return m_TextureImageView;
    }
	[[nodiscard]] const VkSampler GetTextureSampler() const
    {
        return m_TextureSampler;
    }
private:
    std::string m_TexturePath;

    VkImage m_TextureImage{};
    VkDeviceMemory m_TextureImageMemory{};
    VkImageView m_TextureImageView{};
    VkSampler m_TextureSampler{};

    VkDescriptorImageInfo m_ImageInfo{};

    void CreateTextureImage();
    void CreateTextureImageView();
    void CreateTextureSampler();
};
