#pragma once

#include <vector>
#include <unordered_set>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "SharedState/SharedState.hpp"
#include "Mesher/Mesher.hpp"
#include "SharedState/ChunckMap.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Voxel Factory"

namespace VoxelFactory
{
class Renderer {
 public:
    Renderer(SharedState &state);
    ~Renderer();

    void uploadMeshToGPU(const MeshData &mesh);
    void storeForRendering(const glm::ivec3 pos);
    void renderFrame();
    void fetchInputs(ThreadSafeQueue<InputEvent> &inputEvents,
      GLFWwindow *window);

    GLFWwindow *getWindow();

 private:
    std::unordered_set<glm::ivec3, IVec3Hash, IVec3Equal> _meshMap;
    GLFWwindow *_window;
};

void rendererThread(SharedState &state);
} // namespace VoxelFactory
