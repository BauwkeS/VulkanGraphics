#pragma once

#include <memory>
#include <vector>

#include "Texture.h"

class Buffer;

class Material
{
public:
    Material(const std::vector<const Texture*>& textures);

    void MakeUBOStuff(const std::vector<const Texture*>& textures,
        std::vector<Buffer*> uboBuffers);

    void Free();

	[[nodiscard]] inline VkDescriptorSet GetMaterialDescriptorSet() const
    {
        return m_DescriptorSet;
    }

private:
    VkDescriptorSet m_DescriptorSet{};
};
