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

    void DestroyTexture();

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

    VkImageView GetTextureImageView() { return m_TextureImageView; }
    VkSampler GetTextureSampler() { return m_TextureSampler; }

    void CreateTextureDescriptorSet();
private:
    std::string m_TexturePath;

    //uint32_t m_MipLevels{};
    VkImage m_TextureImage{};
    VkDeviceMemory m_TextureImageMemory{};
    VkImageView m_TextureImageView{};
    VkSampler m_TextureSampler{};
    

    void CreateTextureImage();
    void CreateTextureImageView();
    void CreateTextureSampler();

    /*static bool HasStencilComponent(VkFormat format);

    void GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth,
        int32_t texHeight, uint32_t mipLevels);*/
};
