#include "Physics.hpp"

void Physics::Update() {
    for (auto& body : bodies) {
        body.state.position += {0, 0.5};
    }
}

void Physics::AddBody(Shape shape, WorldState state) {
    bodies.emplace_back(std::move(shape), std::move(state));
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
