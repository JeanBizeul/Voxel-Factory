#include "VertexBuffer.hpp"

#include "glad/glad.h"

OpenGLUtils::VertexBuffer::VertexBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLUtils::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_id);
}

OpenGLUtils::VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept
{
    _id = other._id;
    other._id = 0;
}

OpenGLUtils::VertexBuffer &OpenGLUtils::VertexBuffer::operator=(VertexBuffer &&other) noexcept
{
    if (this != &other) {
        glDeleteBuffers(1, &_id);
        _id = other._id;
        other._id = 0;
    }
    return *this;
}

void OpenGLUtils::VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void OpenGLUtils::VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
