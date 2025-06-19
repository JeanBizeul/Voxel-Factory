#include "Mesher.hpp"

#include <iostream>
#include <thread>

#include "Logger/Logger.hpp"
#include "SharedState/SharedState.hpp"

VoxelFactory::Chunk VoxelFactory::generateChunk(const glm::ivec3 &pos)
{
    Chunk chunk;

    chunk.pos = pos;
    chunk.blocks.resize(CHUNK_VOLUME, 0);  // 0 == air
    return chunk;
}

VoxelFactory::MeshData VoxelFactory::generateMesh(const Chunk &chunk)
{
    MeshData mesh;

    mesh.chunkPosition = chunk.pos;
    return mesh;
}

void VoxelFactory::chunckMesherThread(SharedState &state)
{
    LOG_INFO("Started mesher thread");
    while (state.running) {
        auto chunkOpt = state.chunksToGenerate.wait_and_pop();
        
        if (!chunkOpt.has_value())
        break;
        
        glm::ivec3 chunkPos = chunkOpt.value();
        Chunk chunk = std::move(generateChunk(chunkPos));
        MeshData mesh = std::move(generateMesh(chunk));
        state.readyMeshes.push(mesh);
    }
    LOG_INFO("Stopped mesher thread");
}
