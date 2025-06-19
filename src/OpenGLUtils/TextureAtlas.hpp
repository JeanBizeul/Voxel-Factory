#pragma once

#include <string>
#include <unordered_map>

#include "glm/vec2.hpp"

namespace OpenGLUtils
{

typedef struct UVRect_s {
    glm::vec2 uvMin;  // Top left corner  (0.0f, 0.0f)
    glm::vec2 uvMax;  // Top right corner (0.5f, 0.5f)
} UVRect_t;

class TextureAtlas
{
 public:
    TextureAtlas() = delete;
    TextureAtlas(const std::string &path, int tileWidth, int tileHeight);

    TextureAtlas(const TextureAtlas &other) = delete;
    TextureAtlas &operator=(const TextureAtlas &other) = delete;

    void bind();

    UVRect_t getUVRect(const std::string &blockName) const;
 private:
    unsigned int _id;

    const int _tileWidth;
    const int _tileHeight;
    int _atlasWidth;
    int _atlasHeight;

    std::unordered_map<std::string, UVRect_t> _uvMap;
};

}  // namespace OpenGLUtils
