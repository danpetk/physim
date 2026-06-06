#include "VertexArray.hpp"

#include <ranges>

#include "../utils.hpp"

using utils::BindLock;

VertexArray::VertexArray() noexcept {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() noexcept {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const noexcept {
    glBindVertexArray(id);
}

void VertexArray::Unbind() const noexcept {
    glBindVertexArray(0);
}

void VertexArray::BindVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    BindLock a{*this}; 
    BindLock b{vb};
    layout.SetAndEnableAttribPointers();
}