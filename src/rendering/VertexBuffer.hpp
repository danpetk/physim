#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include <span>

class VertexBuffer {
public:
    VertexBuffer() noexcept;
    ~VertexBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;
    
    // Allocating a new buffer every frame is probably not a good idea
    template <typename V>
    void CreateNewBufferWithData(std::span<const V> data, GLenum type) {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(V), data.data(),type);
    }

    void CreateNewBuffer(GLsizeiptr size, GLenum type) {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, type);
    }

    template <typename V>
    void BufferSubData(std::span<const V> data) {
        Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(V), data.data());
    }
private:
    GLuint id;
};