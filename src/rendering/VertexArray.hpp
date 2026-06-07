#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ElementBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
public:
    VertexArray() noexcept;
    ~VertexArray() noexcept;

    void Bind() const noexcept;
    void Unbind() const noexcept;

    void BindVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void BindElementBuffer(const ElementBuffer& eb);
private:
    GLuint id;
};