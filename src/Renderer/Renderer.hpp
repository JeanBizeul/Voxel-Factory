#pragma once

#include <vector>
#include <unordered_map>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "SharedState/SharedState.hpp"
#include "Mesher/Mesher.hpp"
#include "SharedState/ChunckMap.hpp"
#include "OpenGLUtils/TextureAtlas.hpp"
#include "OpenGLUtils/Mesh.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Voxel Factory"

namespace VoxelFactory
{
class Renderer {
 public:
    Renderer(SharedState &state);
    ~Renderer();

    void storeForRendering(const MeshData &meshData);
    void renderFrame();
    void fetchInputs(ThreadSafeQueue<InputEvent> &inputEvents,
      GLFWwindow *window);

    GLFWwindow *getWindow();
 private:
    std::unordered_map<glm::ivec3, std::unique_ptr<OpenGLUtils::Mesh>,
        IVec3Hash, IVec3Equal> _meshes;
    GLFWwindow *_window;
    std::unique_ptr<OpenGLUtils::TextureAtlas> _textureAtlas;
};

void rendererThread(SharedState &state);
} // namespace VoxelFactory
