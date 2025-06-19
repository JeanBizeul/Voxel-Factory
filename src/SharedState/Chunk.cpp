#include "Chunk.hpp"

inline unsigned int VoxelFactory::Chunk::chunkIndex
    (unsigned char x, unsigned char y, unsigned char z) const
{
    return x + CHUNK_SIZE_X * (z + CHUNK_SIZE_Z * y);
}

VoxelFactory::blockId VoxelFactory::Chunk::get(unsigned char x, unsigned char y, unsigned char z) const
{
    unsigned int index = chunkIndex(x, y, z);

    if (index > CHUNK_VOLUME) return 0;
    return blocks[index];
}

void VoxelFactory::Chunk::set(unsigned char x, unsigned char y, unsigned char z, blockId id)
{
    unsigned int index = chunkIndex(x, y, z);

    if (index > CHUNK_VOLUME) return;
    blocks[index] = id;
}

bool VoxelFactory::Chunk::isAirOrOutOfBounds(unsigned char x, unsigned char y, unsigned char z) const
{
    if (x < 0 || x >= CHUNK_SIZE_X
        || y < 0 || y >= CHUNK_SIZE_Y
        || z < 0 || z >= CHUNK_SIZE_Z)
        return true;
    return get(x, y, z) == 0;
}
