#include "Mesher.hpp"

#include "glm/vec3.hpp"

#include "Logger/Logger.hpp"

static constexpr glm::vec3 DIRECTIONS[6] {
    { 0, 0,-1},  // Front
    { 0, 0, 1},  // Back
    {-1, 0, 0},  // Left
    { 1, 0, 0},  // Right
    { 0,-1, 0},  // Bottom
    { 0, 1, 0},  // Top
};

/**
 * If you represent yourself a cube which spans xyz + 1 in each axis.
 * You will get 8 points. I got them in this way :
 * Top face, from (1,1,1) & anti_clockwise: ABCD
 * Bottom face, from (1,0,1) & anti_clockwise: EFGh
 *
 * You will get :
 * | Point | X | Y | Z |
 * |:-----:|---|---|---|
 * | A     | 1 | 1 | 1 |
 * | B     | 1 | 1 | 0 |
 * | C     | 0 | 1 | 0 |
 * | D     | 0 | 1 | 1 |
 * | E     | 1 | 0 | 1 |
 * | F     | 1 | 0 | 0 |
 * | G     | 0 | 0 | 0 |
 * | H     | 0 | 0 | 1 |
 *
 * You can now compose the 8 faces with these 8 points !
 * (That what this FACE_VERTICES does btw)
 */

static constexpr glm::vec3 POINT_A {1, 1, 1};
static constexpr glm::vec3 POINT_B {1, 1, 0};
static constexpr glm::vec3 POINT_C {0, 1, 0};
static constexpr glm::vec3 POINT_D {0, 1, 1};
static constexpr glm::vec3 POINT_E {1, 0, 1};
static constexpr glm::vec3 POINT_F {1, 0, 0};
static constexpr glm::vec3 POINT_G {0, 0, 0};
static constexpr glm::vec3 POINT_H {0, 0, 1};
static constexpr glm::vec3 FACE_VERTICES[6][4] {
    // Front
    {POINT_A, POINT_D, POINT_H, POINT_E},
    // Back
    {POINT_B, POINT_C, POINT_G, POINT_F},
    // Left
    {POINT_D, POINT_C, POINT_G, POINT_H},
    // Right
    {POINT_A, POINT_B, POINT_F, POINT_E},
    // Bottom
    {POINT_E, POINT_F, POINT_G, POINT_H},
    // Top
    {POINT_A, POINT_D, POINT_C, POINT_B}
};

constexpr glm::vec2 UVS[4] {
    {0, 0}, {1, 0}, {1, 1}, {0, 1}
};

VoxelFactory::MeshData VoxelFactory::generateMesh(const Chunk &chunk)
{
    MeshData mesh;

    LOG_DEBUG("Generating mesh ({}, {}, {})", chunk.pos.x, chunk.pos.y, chunk.pos.z);
    mesh.chunkPosition = chunk.pos;

    for (int y = 0; y < CHUNK_SIZE_Y; y++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            for (int x = 0; x < CHUNK_SIZE_X; x++) {
                blockId id = chunk.get(x, y, z);
                if (id == 0)
                    continue;

                    glm::vec3 blockPos = glm::vec3(x, y, z);

                    for (int face = 0; face < 6; face++) {
                        // Check if face needs to be displayed
                        int nx = x + static_cast<int>(DIRECTIONS[face].x);
                        int ny = y + static_cast<int>(DIRECTIONS[face].y);
                        int nz = z + static_cast<int>(DIRECTIONS[face].z);
                        if (!chunk.isAirOrOutOfBounds(nx, ny, nz))
                            continue;

                        // Create the quad (2 triangles)
                        unsigned int indexOffset = mesh.vertices.size();

                        for (int i = 0; i < 4; i++) {
                            OpenGLUtils::Vertex_t v;

                            v.position = blockPos + FACE_VERTICES[face][i];
                            v.normal = DIRECTIONS[face];
                            v.uv = UVS[i];
                            mesh.vertices.push_back(v);
                        }

                        mesh.indices.insert(mesh.indices.end(), {
                            indexOffset + 0, indexOffset + 1, indexOffset + 2,
                            indexOffset + 0, indexOffset + 2, indexOffset + 3
                        });
                    }
            }
        }
    }
    return mesh;
}
