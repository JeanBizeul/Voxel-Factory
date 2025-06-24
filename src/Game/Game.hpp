#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "glm/vec3.hpp"

#include "SharedState/SharedState.hpp"
#include "SharedState/ChunckMap.hpp"

#define RENDER_DISTANCE 5

namespace VoxelFactory
{
class Game {
 public:
    Game() = default;
    ~Game() = default;

    std::vector<glm::ivec3> getVisibleChunks(const glm::vec3 &camPos);

    void manageEvents(SharedState &state);

 private:
    std::unordered_set<glm::ivec3, IVec3Hash, IVec3Equal> _loadedChunks;
    float _deltaTime;

    typedef enum KeyStatus_e {
        Released,
        Pressed,
        Hold
    } KeyStatus_t;
    std::unordered_map<int, KeyStatus_t> _keyStatusMap;
    void _handleKeyPressed(int key, SharedState &state);
    void _handleKeyRelease(int key, SharedState &state);
    bool _cameraCanMove = false;
    std::unordered_map<int, KeyStatus_t> _mouseButtonStatusMap;
    void _handleMouseButtonPressed(int button, SharedState &state);
    void _handleMouseButtonReleased(int button, SharedState &state);
    void _handleMouseMouve(double x, double y, SharedState &state);
    void _handleMouseScroll(double x, double y, SharedState &state);
};

void gameSimulationThread(SharedState &state);
} // namespace VoxelFactory

