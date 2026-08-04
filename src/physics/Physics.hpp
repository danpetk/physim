#pragma once

#include <algorithm>
#include <span>
#include <optional>
#include <utility>
#include <vector>
#include <print>

#include "Shape.hpp"

struct Collision {
    double depth = 0;
    Vec2<double> normal;
};

struct CollisionInfo {
    size_t bodyIndex1 = 0;
    size_t bodyIndex2 = 0;
    Collision collision;
};

class Physics {
public:
    Physics();
    void AddBody(Body body);
    void Update(double dt);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private:  
    void IntegrateVelocity(double dt);
    void IntegratePosition(double dt);
    void DetectCollisions();
    void ResolveCollisionsVelocity();
    void ResolveCollisionsPositions();
    

    std::optional<Collision> BodiesCollideSAT(const auto& shape1, const WorldState& state1, const auto& shape2, const WorldState& state2) {
        auto normals1 = shape1.GetNormalizedNormals(state1);
        auto normals2 = shape2.GetNormalizedNormals(state2);

        auto vertices1 = shape1.GetVertices(state1);
        auto vertices2 = shape2.GetVertices(state2);

        double collisionDepth = std::numeric_limits<double>::max();
        Vec2<double> collisionNormal;

        auto projectOntoAxis = [](const auto& vertices, Vec2<double> normalizedAxis) {
            double min = std::numeric_limits<double>::max();
            double max = std::numeric_limits<double>::lowest();
            for (auto vertex : vertices) {
                double product = vertex.Dot(normalizedAxis);
                min = std::min(min, product);
                max = std::max(max, product);
            }
            return std::pair{min, max};
        };

        auto checkAxesForCollision = [&](const auto& axes) {
            for (const auto& axis : axes) {
                auto [s1min, s1max] = projectOntoAxis(vertices1, axis);
                auto [s2min, s2max] = projectOntoAxis(vertices2, axis);

                double overlap = std::min(s1max, s2max) - std::max(s1min, s2min);

                if (overlap < 0) {
                    return false;
                }

                if (overlap < collisionDepth) {
                    collisionDepth = overlap;
                    collisionNormal = axis;
                }
            }    
            return true;
        };

        if (!checkAxesForCollision(normals1) || !checkAxesForCollision(normals2)) {
            return std::nullopt;
        }

        // We do this to ensure our vector to fix the collision is facing the right way
        Vec2<double> positionDiff = state2.position - state1.position;
        if (collisionNormal.Dot(positionDiff) < 0) {
            collisionNormal = -collisionNormal;
        }

        return Collision{collisionDepth, collisionNormal};
    }

    std::vector<Body> bodies;
    std::vector<CollisionInfo> collisionsThisFrame;
};