#include "SharedState.hpp"

void VoxelFactory::SharedState::stopApp()
{
    this->running = false;
    this->chunksToGenerate.stop();
    this->readyMeshes.stop();
}

void VoxelFactory::SharedState::setChunk(const glm::ivec3 &pos, const Chunk &chunk)
{
    std::lock_guard<std::mutex> lock(_worldMutex);
    _chunkMap[pos] = chunk;
}

std::optional<VoxelFactory::Chunk> VoxelFactory::SharedState::getChunk
(const glm::ivec3 &pos) const
{
    std::lock_guard<std::mutex> lock(_worldMutex);
    auto it = _chunkMap.find(pos);
    if (it == _chunkMap.end()) return std::nullopt;
    return it->second;
}

void VoxelFactory::SharedState::setCameraPosition(const glm::ivec3 &pos)
{
    std::lock_guard<std::mutex> lock(_cameraMutex);
    _cameraPos = pos;
}

const glm::ivec3 &VoxelFactory::SharedState::getCameraPosition() const
{
    std::lock_guard<std::mutex> lock(_cameraMutex);
    return _cameraPos;
}
