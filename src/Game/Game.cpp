#include "Game.hpp"

#include <thread>

#include "Logger/Logger.hpp"

std::vector<glm::ivec3> VoxelFactory::Game::getVisibleChunks(const glm::vec3 &camPos)
{
    glm::ivec3 actualChunk = camPos / CHUNK_SIZE;
    std::vector<glm::ivec3> visibleChunks;

    for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; ++x) {
        for (int z = -RENDER_DISTANCE; z <= RENDER_DISTANCE; ++z) {
            glm::ivec3 chunkPos = actualChunk + glm::ivec3(x, 0, z);
            if (_loadedChunks.find(chunkPos) == _loadedChunks.end()) {
                visibleChunks.emplace_back(chunkPos);
                _loadedChunks.emplace(chunkPos);
            }
        }
    }
    return visibleChunks;
}

void VoxelFactory::gameSimulationThread(VoxelFactory::SharedState &state)
{
    Game game;

    LOG_INFO("Started game simulation thread");
    while (state.running) {
        game.manageEvents(state);
        for (const auto& newChunkPos : game.getVisibleChunks(state.camera().getTargetPosition())) {
            state.chunksToGenerate.push(newChunkPos);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LOG_INFO("Stopped simulation thread");
}
