#include "IndexBuffer.hpp"

#include "glad/glad.h"

OpenGLUtils::IndexBuffer::IndexBuffer(const void *data, size_t size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

OpenGLUtils::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &_id);
}

OpenGLUtils::IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept
{
    _id = other._id;
    other._id = 0;
}

OpenGLUtils::IndexBuffer &OpenGLUtils::IndexBuffer::operator=(IndexBuffer &&other) noexcept
{
    if (this != &other) {
        glDeleteBuffers(1, &_id);
        _id = other._id;
        other._id = 0;
    }
    return *this;
}

void OpenGLUtils::IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void OpenGLUtils::IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
