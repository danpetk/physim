#include "Renderer.hpp"

Renderer::Renderer() {
    
}

void Renderer::DrawBodies(std::span<const Body> bodies) {
    for (const auto& body: bodies) {
        std::visit([&] (const auto& shape) {
            // Draw(shape, body.position);
        }, body.shape);
    }
}