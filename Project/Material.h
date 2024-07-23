#pragma once

#include <vector>

#include "Texture.h"

class Buffer;

class Material
{
public:
    Material(const std::vector<const Texture*>& textures);

	[[nodiscard]] inline VkDescriptorSet GetMaterialDescriptorSet() const
    {
        return m_DescriptorSet;
    }

private:
    VkDescriptorSet m_DescriptorSet{};
};
