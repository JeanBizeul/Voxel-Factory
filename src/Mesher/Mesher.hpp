#pragma once

#include <vector>
#include <cstdint>

#include "glm/vec3.hpp"
#include "SharedState/Chunk.hpp"
#include "OpenGLUtils/Vertex.hpp"

namespace VoxelFactory {
class SharedState;

struct MeshData {
    glm::vec3 chunkPosition;
    // Rendering stuff
    std::vector<OpenGLUtils::Vertex_t> vertices;
    std::vector<unsigned int> indices;
};

Chunk generateChunk(const glm::ivec3 &chunkPos);

MeshData generateMesh(const Chunk &chunk);

void chunckMesherThread(SharedState &state);
}  // namespace VoxelFactory
