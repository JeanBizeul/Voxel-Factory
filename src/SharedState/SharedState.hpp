#pragma once

#include <mutex>
#include <unordered_map>
#include <atomic>
#include "glm/vec3.hpp"

#include "ThreadSafeQueue.hpp"
#include "ChunckMap.hpp"
#include "Mesher/Mesher.hpp"
#include "Event.hpp"
#include "SafeCamera.hpp"

constexpr float CHUNK_SIZE = 16.0f;

namespace VoxelFactory {

class SharedState {
 public:
    SharedState() = default;
    ~SharedState() = default;

    ThreadSafeQueue<glm::ivec3> chunksToGenerate;
    ThreadSafeQueue<MeshData> readyMeshes;
    ThreadSafeQueue<InputEvent> inputEvents;

    std::atomic<bool> running = true;
    void stopApp();

    void setChunk(const glm::ivec3 &pos, const Chunk &chunk);
    std::optional<Chunk> getChunk(const glm::ivec3 &pos) const;

    SafeCamera &camera();

    std::atomic<bool> cameraCanMove;
    std::atomic<bool> cursorTrapped;

 private:
    std::unordered_map<glm::ivec3, Chunk, IVec3Hash, IVec3Equal> _chunkMap;
    mutable std::mutex _worldMutex;
    SafeCamera _camera;
};
}
