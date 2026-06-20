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

    void CreateNewBufferWithData(std::span<const GLuint> data, GLenum type) {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), type);
    }

    void CreateNewBuffer(GLsizeiptr size, GLenum type) {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, type);
    }

    void BufferSubData(std::span<const GLuint> data) {
        Bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.size() * sizeof(GLuint), data.data());
    }
private:
    GLuint id;
};