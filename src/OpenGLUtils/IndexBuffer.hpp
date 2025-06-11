#include <cstddef>

namespace OpenGLUtils
{
/**
 * This class reprsents a ElementBufferObject, it aims to store all indices
 * of an object in an array.
 */
class IndexBuffer {
 public:
    IndexBuffer(const void* data, size_t size);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    void bind() const;
    static void unbind();

 private:
    unsigned int _id = 0;
};
}  // OpenGLUtils
