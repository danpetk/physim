#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer() {
    glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &id);
}