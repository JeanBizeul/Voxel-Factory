#include "Mesher.hpp"

#include <iostream>
#include <thread>

#include "Logger/Logger.hpp"
#include "SharedState/SharedState.hpp"

VoxelFactory::Chunk VoxelFactory::generateChunk(const glm::ivec3 &pos)
{
    Chunk chunk;

    LOG_DEBUG("Generating chunk ({}, {}, {})", pos.x, pos.y, pos.z);
    chunk.pos = pos;
    chunk.blocks.resize(CHUNK_VOLUME, 0);  // 0 == air
    for (int y = 0; y < CHUNK_SIZE_Y; y++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            for (int x = 0; x < CHUNK_SIZE_X; x++) {
                chunk.set(x, y, z, rand() % 3);
            }
        }
    }
    return chunk;
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
