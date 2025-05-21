#pragma once

#include <vector>
#include <unordered_set>

#include "SharedState/SharedState.hpp"
#include "Mesher/Mesher.hpp"
#include "SharedState/ChunckMap.hpp"

namespace VoxelFactory
{
class Renderer {
 public:
    Renderer();
    ~Renderer() = default;

    void uploadMeshToGPU(const MeshData &mesh);
    void storeForRendering(const glm::ivec3 pos);
    void renderFrame();

 private:
    std::unordered_set<glm::ivec3, IVec3Hash, IVec3Equal> _meshMap;
};

void rendererThread(SharedState &state);
} // namespace VoxelFactory
