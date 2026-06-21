#include "Physics.hpp"

Physics::Physics() {
    // floor
    AddBody(
        BodyBuilder{}.MakeBox(100, 1).Position({0, -VIEWPORT_HEIGHT / 2}).InvMass(0).Gravity(Gravity::Static).build()
    );
}

void Physics::Update(double dt) {
    for (auto& body : bodies) {
        body.state.prevPosition = body.state.position;  // save before step
        body.state.velocity += {0, -9.8 * dt * body.state.gravScale};
        body.state.position += body.state.velocity * dt;
    }
}

void Physics::AddBody(Body b) {
    bodies.emplace_back(std::move(b));
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
