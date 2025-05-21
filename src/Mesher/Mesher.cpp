#include "Mesher.hpp"

#include <iostream>
#include <thread>

#include "Logger/Logger.hpp"
#include "SharedState/SharedState.hpp"

VoxelFactory::Chunk VoxelFactory::generateChunk(const glm::ivec3 &pos)
{
    Chunk chunk;

    Logger::getInstance().log("Generating chunk ("
        + std::to_string(pos.x)
        + ", " + std::to_string(pos.y)
        + ", " + std::to_string(pos.z) + ")", "mesher");
    chunk.pos = pos;
    return chunk;
}

VoxelFactory::MeshData VoxelFactory::generateMesh(const Chunk &chunk)
{
    MeshData mesh;

    Logger::getInstance().log("Generating mesh  ("
        + std::to_string(chunk.pos.x)
        + ", " + std::to_string(chunk.pos.y)
        + ", " + std::to_string(chunk.pos.z) + ")", "mesher");
    mesh.chunkPosition = chunk.pos;
    return mesh;
}

void VoxelFactory::chunckMesherThread(SharedState &state)
{
    while (state.running) {
        auto chunkOpt = state.chunksToGenerate.wait_and_pop();

        if (!chunkOpt.has_value())
            break;

        glm::ivec3 chunkPos = chunkOpt.value();
        Chunk chunk = generateChunk(chunkPos);
        MeshData mesh = generateMesh(chunk);
        state.readyMeshes.push(mesh);
    }
    Logger::getInstance().log("Stopped mesher thread", "mesher", Logger::INFO);
}
