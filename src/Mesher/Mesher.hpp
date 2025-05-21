#pragma once

#include <vector>
#include <cstdint>

#include "glm/vec3.hpp"
#include "SharedState/Chunk.hpp"

namespace VoxelFactory {
class SharedState;

struct MeshData {
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    glm::vec3 chunkPosition;
};

Chunk generateChunk(const glm::ivec3 &chunkPos);

MeshData generateMesh(const Chunk &chunk);

void chunckMesherThread(SharedState &state);
}  // namespace VoxelFactory
