#pragma once

#include <algorithm>
#include <span>
#include <optional>
#include <utility>
#include <vector>
#include <print>

#include "Shape.hpp"

struct CollisionInfo {
    size_t bodyIndex1 = 0;
    size_t bodyIndex2 = 0;
    double collisionDepth = 0;
    Vec2<double> collisionNormal;
};

class Physics {
public:
    Physics();
    void AddBody(Body body);
    void Update(double dt);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private:  
    void IntegerateVelocity(double dt);
    void IntegeratePosition(double dt);
    void DetectCollisions();
    void ResolveCollisions() {}
    
    // A wonderful little signature
    // I feel like one return doesnt warrant a struct because I have the other collision info so this is what we are doing
    std::optional<std::pair<double, Vec2<double>>> BodiesCollideSAT(const auto& shape1, const WorldState& state1, const auto& shape2, const WorldState& state2) {
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

        return std::pair{collisionDepth, collisionNormal};
    }

    std::vector<Body> bodies;
    std::vector<CollisionInfo> collisionsThisFrame;
};