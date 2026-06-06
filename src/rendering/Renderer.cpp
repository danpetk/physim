#include "Renderer.hpp"

#include "VertexBufferLayout.hpp"

Renderer::Renderer() {

    VertexBufferLayout layout;
    layout.AddAttribute<double>(2);
    array.BindVertexBuffer(buf, layout);
}

void Renderer::DrawBodies(std::span<const Body> bodies) {
    for (const auto& body: bodies) {
        std::visit([&] (const auto& shape) {
            // Draw(shape, body.position);
        }, body.shape);
    }
}