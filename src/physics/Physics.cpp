#include "Physics.hpp"

Physics::Physics() {
    // floor
    AddBody(Box{100, 1}, {{0, -VIEWPORT_HEIGHT / 2}, {0,0}, 0, Gravity::Static});
}

void Physics::Update(double dt) {
    for (auto& body : bodies) {
        body.state.prevPosition = body.state.position;  // save before step
        body.state.velocity += {0, -9.8 * dt * body.state.gravScale};
        body.state.position += body.state.velocity * dt;
    }
}

void Physics::AddBody(Shape shape, WorldState state) {
    bodies.emplace_back(std::move(shape), std::move(state));
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
