#include "Game.hpp"

#include <thread>

#include "Logger/Logger.hpp"

std::vector<glm::ivec3> VoxelFactory::Game::getVisibleChunks()
{
    glm::ivec3 actualChunk = _camPos / CHUNK_SIZE;
    std::vector<glm::ivec3> visibleChunks;

    for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; ++x) {
        for (int y = -RENDER_DISTANCE; y <= RENDER_DISTANCE; ++y) {
            glm::ivec3 chunkPos = actualChunk + glm::ivec3(x, y, 0);
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
        for (const auto& newChunkPos : game.getVisibleChunks()) {
            state.chunksToGenerate.push(newChunkPos);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    LOG_INFO("Stopped simulation thread");
}
