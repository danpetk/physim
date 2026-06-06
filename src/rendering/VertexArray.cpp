#include "VertexArray.hpp"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() {
    glBindVertexArray(id);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
}