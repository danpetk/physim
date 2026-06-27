#pragma once

#include <algorithm>
#include <span>
#include <vector>
#include <print>

#include "Shape.hpp"

struct CollisionInfo {
    size_t bodyIndex1;
    size_t bodyIndex2;
};

class Physics {
public:
    Physics();
    void AddBody(Body body);
    void Update(double dt);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private:  
    void Integerate(double dt);
    void DetectCollisions();
    
    bool BodiesCollideSAT(const auto& shape1, const WorldState& state1, const auto& shape2, const WorldState& state2) {
        auto normals1 = shape1.GetNormalizedNormals(state1);
        auto normals2 = shape2.GetNormalizedNormals(state2);

        auto verticies1 = shape1.GetVertices(state1);
        auto verticies2 = shape2.GetVertices(state2);

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

        // TODO Fix this duplication
        for (const auto& axis : normals1) {
            auto [s1min, s1max] = projectOntoAxis(verticies1, axis);
            auto [s2min, s2max] = projectOntoAxis(verticies2, axis);

            if (!(s1min <= s2max && s2min <= s1max)) {
                return false;
            }
        }
        
        for (const auto& axis : normals2) {
            auto [s1min, s1max] = projectOntoAxis(verticies1, axis);
            auto [s2min, s2max] = projectOntoAxis(verticies2, axis);

            if (!(s1min <= s2max && s2min <= s1max)) {
                return false;
            }
        }

        return true;
    }

    std::vector<Body> bodies;
    std::vector<CollisionInfo> collisionsThisFrame;
};