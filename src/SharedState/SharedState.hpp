#pragma once

#include <mutex>
#include <unordered_map>
#include <atomic>
#include "glm/vec3.hpp"

#include "ThreadSafeQueue.hpp"
#include "ChunckMap.hpp"
#include "Mesher/Mesher.hpp"

#define CHUNK_SIZE 16

namespace VoxelFactory {

class SharedState {
 public:
    SharedState() = default;
    ~SharedState() = default;
    
    ThreadSafeQueue<glm::ivec3> chunksToGenerate;
    ThreadSafeQueue<MeshData> readyMeshes;

    std::atomic<bool> running = true;
    void stopApp();

    void setChunk(const glm::ivec3 &pos, const Chunk &chunk);
    std::optional<Chunk> getChunk(const glm::ivec3 &pos) const;

    void setCameraPosition(const glm::ivec3 &pos);
    const glm::ivec3 &getCameraPosition() const;

 private:
    std::unordered_map<glm::ivec3, Chunk, IVec3Hash, IVec3Equal> _chunkMap;
    mutable std::mutex _worldMutex;
    glm::ivec3 _cameraPos;
    mutable std::mutex _cameraMutex;
};
}
