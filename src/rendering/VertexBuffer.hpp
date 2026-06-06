#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
public:
    VertexBuffer() noexcept;
    ~VertexBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;
private:
    GLuint id;
};