#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() noexcept {
    glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer() noexcept {
    glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind() const noexcept {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind() const noexcept {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}