#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace OpenGLUtils
{
    typedef struct Vertex_s {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    } Vertex_t;
}
