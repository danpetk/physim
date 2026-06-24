#pragma once

#include <algorithm>
#include <span>
#include <vector>
#include <print>

#include "Shape.hpp"

class Physics {
public:
    Physics();
    void AddBody(Body body);
    void Update(double dt);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private:  
    void Integerate(double dt);
    void DetectCollisions();
    
    bool BodiesCollideSAT(const auto& shape1, WorldState& state1, const auto& shape2, WorldState& state2) {

        std::vector<Vec2<double>> normals {{1,0}, {0, 1}};
        auto v1 = shape1.GetVertices(state1);
        auto v2 = shape2.GetVertices(state2);

        for (const auto& normal : normals) {
            auto s1minx = std::ranges::min(v1, {}, &Vec2<double>::x).x;
            auto s1maxx = std::ranges::max(v1, {}, &Vec2<double>::x).x;
            auto s1miny = std::ranges::min(v1, {}, &Vec2<double>::y).y;
            auto s1maxy = std::ranges::max(v1, {}, &Vec2<double>::y).y;

            auto s2minx = std::ranges::min(v2, {}, &Vec2<double>::x).x;
            auto s2maxx = std::ranges::max(v2, {}, &Vec2<double>::x).x;
            auto s2miny = std::ranges::min(v2, {}, &Vec2<double>::y).y;
            auto s2maxy = std::ranges::max(v2, {}, &Vec2<double>::y).y;
        
            bool overlapsX = s1minx <= s2maxx && s2minx <= s1maxx;
            bool overlapsY = s1miny <= s2maxy && s2miny <= s1maxy;

            if (!overlapsX || !overlapsY) {
                return false;
            }       
        
        }

        return true;
    }

    bool stop = false;
    std::vector<Body> bodies;
};