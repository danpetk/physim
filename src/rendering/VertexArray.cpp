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

void VertexArray::BindVertexBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, GLuint div) {
    Bind();
    vb.Bind();

    for (const auto& attrib : layout.GetAttributes() ) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index, 
            attrib.size, 
            attrib.type, 
            attrib.normalized, 
            layout.GetStride(), 
            reinterpret_cast<const GLvoid*>(attrib.offset)
        );
        glVertexAttribDivisor(index, div);
        ++index;
    }
}

void VertexArray::BindElementBuffer(const ElementBuffer& eb) {
    Bind();
    eb.Bind();
}
