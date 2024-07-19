#pragma once

#include <vector>

#include "Texture.h"

class Material
{
public:
    Material(const std::vector<const Texture*>& textures);

    void CreateDefaultTextures();

    void Free();

    [[nodiscard]] inline VkDescriptorSet GetMaterialDescriptorSet() const
    {
        return m_DescriptorSet;
    }

private:
    VkDescriptorSet m_DescriptorSet{};
};
