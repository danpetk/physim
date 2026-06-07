#pragma once

#include <span>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ElementBuffer {
public:
    ElementBuffer() noexcept;
    ~ElementBuffer() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    // Allocating a new buffer every frame is probably not a good idea, so this will
    // most likely be replaced / not used at the end
    void AllocNewBufferData(std::span<GLuint> data) {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_DYNAMIC_DRAW);
    }
private:
    GLuint id;
};