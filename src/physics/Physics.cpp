#include "Physics.hpp"

void Physics::Update(double dt) {
    for (auto& body : bodies) {
        body.state.velocity += {0, -9.8 * dt};
        body.state.position += body.state.velocity * dt;
    }
}

void Physics::AddBody(Shape shape, WorldState state) {
    bodies.emplace_back(std::move(shape), std::move(state));
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
