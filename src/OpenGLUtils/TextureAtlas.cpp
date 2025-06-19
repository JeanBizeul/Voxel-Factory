#include "TextureAtlas.hpp"

#include <filesystem>
#include <iostream>

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION  // Required to make stb_image work
#define STBI_ONLY_PNG             // Only compiles the PNG module
#include "STBImage/stb_image.h"

#include "Logger/Logger.hpp"

static void loadImage(const std::string &path)
{
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!data) {
        LOG_ERROR("Failed to load image '{}': {}", path, stbi_failure_reason());
    } else {
        LOG_DEBUG("Loaded '{}'", path);
        free(data);
    }
}

OpenGLUtils::TextureAtlas::TextureAtlas(const std::string &path, int tileWidth, int tileHeight)
    : _tileWidth(tileWidth), _tileHeight(tileHeight)
{
    std::filesystem::recursive_directory_iterator it(path);

    LOG_INFO("Loading all png files recursively from '{}'", path);
    for (auto &file : it) {
        if (file.is_regular_file())
            loadImage(file.path());
    }
}

void OpenGLUtils::TextureAtlas::bind()
{
    glBindTexture(GL_TEXTURE0, _id);
}

/// Defaults to give the first texture of the atlas if not found.
OpenGLUtils::UVRect_t OpenGLUtils::TextureAtlas::getUVRect(const std::string &blockName) const
{
    if (_uvMap.find(blockName) == _uvMap.end())
        return {{0.0f, 0.0f}, {_tileWidth, _tileHeight}};
    return _uvMap.find(blockName)->second;
}
