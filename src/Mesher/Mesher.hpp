#pragma once

#include <vector>
#include <cstdint>

#include "glm/vec3.hpp"
#include "SharedState/Chunk.hpp"
#include "OpenGLUtils/Vertex.hpp"

namespace VoxelFactory {
class SharedState;

struct MeshData {
    std::vector<OpenGLUtils::Vertex_t> data;
    glm::vec3 chunkPosition;
    // Used for frustrum culling
    glm::vec3 boundsMin;
    glm::vec3 boundsMax;
};

Chunk generateChunk(const glm::ivec3 &chunkPos);

MeshData generateMesh(const Chunk &chunk);

void chunckMesherThread(SharedState &state);
}  // namespace VoxelFactory
