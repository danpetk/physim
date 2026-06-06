#pragma once

#include <span>
#include <vector>

#include "Body.hpp"

class Physics {
public:
    void AddBody(Shape shape, Vec2 position, double mass);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private: 
    std::vector<Body> bodies;
};