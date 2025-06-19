#pragma once
#include "glm/vec3.hpp"

namespace VoxelFactory
{

constexpr unsigned char CHUNK_SIZE_X = 16;
constexpr unsigned char CHUNK_SIZE_Y = 16;
constexpr unsigned char CHUNK_SIZE_Z = 16;
constexpr int CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;

/**
 * @brief Each block is associated with a specific id, 0 is reserved for air
 * @remark The size (unsigned char) may be changed later on. But it sould
 * be plenty for now.
 */
using blockId = unsigned char;

class Chunk
{
 public:
    Chunk() = default;
    ~Chunk() = default;

    glm::ivec3 pos;
    std::vector<blockId> blocks;

    blockId get(unsigned char x, unsigned char y, unsigned char z) const;
    void set(unsigned char x, unsigned char y, unsigned char z, blockId id);

    bool isAirOrOutOfBounds(unsigned char x, unsigned char y, unsigned char z) const;

 private:
    /**
     * @brief Get the index of a block in a chunk internal vector with xyz coordinates
     */
    inline unsigned int chunkIndex(unsigned char x, unsigned char y, unsigned char z) const;
};

}
