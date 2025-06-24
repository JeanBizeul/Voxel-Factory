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
#include "OpenGLUtils/Shader.hpp"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define WINDOW_NAME "Voxel Factory"

namespace VoxelFactory
{

void scrollCallback(GLFWwindow *, double xoffset, double yoffset);
void mouseMovedCallback(GLFWwindow* window, double xpos, double ypos);

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
    SharedState &_state;
    std::unordered_map<glm::ivec3, std::unique_ptr<OpenGLUtils::Mesh>,
        IVec3Hash, IVec3Equal> _meshes;
    GLFWwindow *_window;
    std::unique_ptr<OpenGLUtils::TextureAtlas> _textureAtlas;
    std::unique_ptr<OpenGLUtils::Shader> _blockShader;

    std::unordered_map<int, int> _prevKeyStates;
    std::unordered_map<int, int> _prevMouseStates;

    void renderBlocks();
};

void rendererThread(SharedState &state);
} // namespace VoxelFactory
