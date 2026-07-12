#include "Physics.hpp"

#include <print>

Physics::Physics() {
    // floor
    AddBody(
        BodyBuilder{}.MakeBox(100, 1).Position({0, -VIEWPORT_HEIGHT / 2}).InvMass(0).GravOpt(Gravity::Static).build()
    );
}

/**
 * TODO: Unoptimized so stacks and collisions are stable.
 * Works for now so I can continue development but revisit in the future
 */
void Physics::Update(double dt) {
    constexpr int substeps = 4;
    double subDt = dt / substeps;

    for (int s = 0; s < substeps; ++s) {
        IntegrateVelocity(subDt);
        IntegratePosition(subDt);
    
        DetectCollisions();

        for (int i = 0; i < 10; ++i) {
            DetectCollisions();
            ResolveCollisionsVelocity();
        }
        for (int i = 0; i < 2; ++i) {
            DetectCollisions();
            ResolveCollisionsPositions();
        }
    }
}

void Physics::IntegrateVelocity(double dt) {
    for (auto& body : bodies) {
        body.state.velocity += {0, -9.8 * dt * body.state.gravScale};
    }
}

void Physics::IntegratePosition(double dt) {
    for (auto& body : bodies) {
        body.state.prevPosition = body.state.position;  // save before step
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
                if (auto info = BodiesCollideSAT(shape1, body1.state, shape2, body2.state)) {
                    collisionsThisFrame.emplace_back(i, j, info->first, info->second);
                }
            }, body1.shape, body2.shape);
        }
    }
}

void Physics::ResolveCollisionsVelocity() {
    for (const auto& collision : collisionsThisFrame) {
        WorldState& state1 = bodies[collision.bodyIndex1].state;
        WorldState& state2 = bodies[collision.bodyIndex2].state;

        // impulse calculation
        constexpr double e = 0.1;   
        auto relativeVelocity = state1.velocity - state2.velocity;
        double num = -(1 + e) * (relativeVelocity.Dot(collision.collisionNormal));
        double denom = state1.invMass + state2.invMass;
        double impulse = num / denom;

        // velocity update
        state1.velocity += (impulse * state1.invMass) * collision.collisionNormal;
        state2.velocity -= (impulse * state2.invMass) * collision.collisionNormal;
    }
}

void Physics::ResolveCollisionsPositions() {
    for (const auto& collision : collisionsThisFrame) {
        WorldState& state1 = bodies[collision.bodyIndex1].state;
        WorldState& state2 = bodies[collision.bodyIndex2].state;

        // no we update the positions to prevent sinking
        constexpr double percent = 0.4;
        constexpr double slop = 0.01;

        double pen = std::max(collision.collisionDepth - slop, 0.0);
        double denom = state1.invMass + state2.invMass;
        Vec2<double> correction = (pen / denom) * percent * collision.collisionNormal;

        // update positions
        state1.position -= state1.invMass * correction;
        state2.position += state2.invMass * correction;
    }
}

void Physics::AddBody(Body b) {
    bodies.emplace_back(std::move(b));
}

std::span<const Body> Physics::GetBodies() const noexcept {
    return bodies;
}
