#include "Game.hpp"

#include <thread>

#include "Logger/Logger.hpp"

void VoxelFactory::Game::updateCamPos(VoxelFactory::SharedState &state)
{
    _camPos += glm::ivec3(1.0, 1.0, 0.0);
    state.setCameraPosition(_camPos);
}

std::vector<glm::ivec3> VoxelFactory::Game::getVisibleChunks()
{
    glm::ivec3 actualChunk = _camPos / CHUNK_SIZE;
    std::vector<glm::ivec3> visibleChunks;

    for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; ++x) {
        for (int y = -RENDER_DISTANCE; y <= RENDER_DISTANCE; ++y) {
            glm::ivec3 chunkPos = actualChunk + glm::ivec3(x, y, 0);
            if (_loadedChunks.find(chunkPos) == _loadedChunks.end()) {
                visibleChunks.emplace_back(chunkPos);
                Logger::getInstance().log("Added ("
                    + std::to_string(chunkPos.x) + ", "
                    + std::to_string(chunkPos.y) + ", "
                    + std::to_string(chunkPos.z) + ")",
                    "simulation");
                _loadedChunks.emplace(chunkPos);
            }
        }
    }
    return visibleChunks;
}

void VoxelFactory::gameSimulationThread(VoxelFactory::SharedState &state)
{
    Game game;

    while (state.running) {
        game.updateCamPos(state);
        for (const auto& newChunkPos : game.getVisibleChunks()) {
            state.chunksToGenerate.push(newChunkPos);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    Logger::getInstance().log("Stopped simulation thread", "simulation", Logger::INFO);
}
