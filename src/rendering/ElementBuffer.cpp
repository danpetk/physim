#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer() noexcept {
    glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer() noexcept {
    glDeleteBuffers(1, &id);
}

void ElementBuffer::Bind() const noexcept {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::Unbind() const noexcept {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}