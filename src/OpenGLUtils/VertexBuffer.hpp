#include <cstddef>

namespace OpenGLUtils
{
/**
 * This class reprsents a VertexBufferObject, it aims to store all vertices
 * of an object in an array.
 */
class VertexBuffer {
 public:
    VertexBuffer(const void* data, size_t size);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void bind() const;
    static void unbind();

 private:
    unsigned int _id = 0;
};
}  // OpenGLUtils
