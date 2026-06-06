#include "Physics.hpp"

void Physics::AddBody(Shape shape, Vec2 position, double mass) {
    bodies.emplace_back(
        std::move(shape),
        position,
        mass
    );
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
