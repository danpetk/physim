#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer() {
    glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &id);
}

void ElementBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}