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

    std::vector<glm::ivec3> getVisibleChunks();

    void manageEvents(SharedState &state);

 private:
    std::unordered_set<glm::ivec3, IVec3Hash, IVec3Equal> _loadedChunks;
    glm::vec3 _camPos;
    float _deltaTime;

    void _handleKeyPressed(int key, SharedState &state);
    void _handleKeyRelease(int key, SharedState &state);
    bool _cameraCanMove = false;
    void _handleMouseButtonPressed(int button, SharedState &state);
    void _handleMouseButtonReleased(int button, SharedState &state);
    void _handleMouseMouve(double x, double y, SharedState &state);
    void _handleMouseScroll(double x, double y, SharedState &state);
};

void gameSimulationThread(SharedState &state);
} // namespace VoxelFactory

