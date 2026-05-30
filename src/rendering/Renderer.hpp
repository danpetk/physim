#pragma once

#include <print>
#include <span>

#include "../physics/Body.hpp"

class Renderer {
public:
    void DrawBodies(std::span<const Body> bodies) {
        for (const auto& body: bodies) {
            std::visit([&] (const auto& shape) {
                Draw(shape, body.position);
            }, body.shape);
        }
    }
private:
    void Draw(const Box& box, Vec2 position) {
        std::println("Drawing box at {} with width {} and height {}.", position, box.width, box.height);
    }

    void Draw(const Circle& box, Vec2 position) {
        std::println("Drawing circle at {} with radius {}.", position, box.radius);
    }
};