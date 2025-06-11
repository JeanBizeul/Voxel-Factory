#pragma once

#include <cstddef>

namespace OpenGLUtils
{
/**
 * This class reprsents a ElementBufferObject, it aims to store all indices
 * of an object in an array.
 */
class IndexBuffer {
 public:
    IndexBuffer(unsigned int *data, size_t count);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer &other) = delete;
    IndexBuffer &operator=(const IndexBuffer &other) = delete;
    IndexBuffer(IndexBuffer &&other) noexcept;
    IndexBuffer &operator=(IndexBuffer &&other) noexcept;

    void bind() const;
    static void unbind();

    unsigned int getCount() const;
    unsigned int getId() const;

 private:
    unsigned int _count;
    unsigned int _id = 0;
};
}  // OpenGLUtils
