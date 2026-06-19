#pragma once

#include <span>
#include <vector>

#include "Shape.hpp"

class Physics {
public:
    void AddBody(Shape shape, WorldState state);
    void Update(double dt);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private: 
    std::vector<Body> bodies;
};