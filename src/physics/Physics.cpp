#include "Physics.hpp"

#include <print>

Physics::Physics() {
    // floor
    AddBody(
        BodyBuilder{}.MakeBox(100, 1).Position({0, -VIEWPORT_HEIGHT / 2}).InvMass(0).GravOpt(Gravity::Static).build()
    );
}

void Physics::Update(double dt) {
    Integerate(dt);
    DetectCollisions();
}

void Physics::Integerate(double dt) {
    for (auto& body : bodies) {
        body.state.prevPosition = body.state.position;  // save before step
        body.state.velocity += {0, -9.8 * dt * body.state.gravScale};
        body.state.position += body.state.velocity * dt;
    }
}

void Physics::DetectCollisions() {
    collisionsThisFrame.clear();

    for (size_t i{0}; i < bodies.size(); ++i) {
        for (size_t j{i+1}; j < bodies.size(); ++j) {
            const Body& body1 = bodies[i];
            const Body& body2 = bodies[j];
            
            std::visit([&](const auto& shape1, const auto& shape2) {
                if (BodiesCollideSAT(shape1, body1.state, shape2, body2.state)) {
                    collisionsThisFrame.emplace_back(i, j);
                    std::println("############### FRAME #####################");
                    std::println("Collision detected on body {} and {}", i, j);
                    std::println("##########################################\n");
                }
            }, body1.shape, body2.shape);
        }
    }
}


void Physics::AddBody(Body b) {
    bodies.emplace_back(std::move(b));
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
