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

    // Allocating a new buffer every frame is probably not a good idea, so this will
    // most likely be replaced / not used at the end
    template <typename V>
    void AllocNewBufferData(std::span<V> data) {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(V), data.data(), GL_DYNAMIC_DRAW);
    }
private:
    GLuint id;
};