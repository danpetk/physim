#include "VertexBufferLayout.hpp"

#include <ranges>

void VertexBufferLayout::SetAndEnableAttribPointers() const {
    for (const auto& [i, attrib] : std::views::enumerate(attributes) ) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, 
            attrib.size, 
            attrib.type, 
            attrib.normalized, 
            stride, 
            reinterpret_cast<const GLvoid*>(attrib.offset)
        );
    }
}
