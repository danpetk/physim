#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ElementBuffer {
public:
    ElementBuffer() noexcept;
    ~ElementBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;
private:
    GLuint id;
};