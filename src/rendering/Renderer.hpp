#pragma once

#include <print>
#include <span>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "../physics/Body.hpp"

class Renderer {
public:
    void DrawBodies(std::span<const Body> bodies) {
        for (const auto& body: bodies) {
            std::visit([&] (const auto& shape) {
                // Draw(shape, body.position);
            }, body.shape);
        }
    }
private:
    VertexArray array;
    VertexBuffer buf;
};