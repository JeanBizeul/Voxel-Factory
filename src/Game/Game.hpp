#pragma once

#include <vector>
#include <unordered_set>

#include "glm/vec3.hpp"

#include "SharedState/SharedState.hpp"
#include "SharedState/ChunckMap.hpp"

#define RENDER_DISTANCE 5

namespace VoxelFactory
{
class Game {
 public:
    Game() : _camPos(0.0f) {}
    ~Game() = default;

    void updateCamPos(SharedState &state);

    std::vector<glm::ivec3> getVisibleChunks();

 private:
    std::unordered_set<glm::ivec3, IVec3Hash, IVec3Equal> _loadedChunks;
    glm::ivec3 _camPos;
};

void gameSimulationThread(SharedState &state);
} // namespace VoxelFactory

