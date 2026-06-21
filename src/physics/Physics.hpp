#pragma once

#include <span>
#include <vector>

#include "Shape.hpp"

class Physics {
public:
    Physics();
    void AddBody(Body body);
    void Update(double dt);
    [[nodiscard]] std::span<const Body> GetBodies() const noexcept;
private: 
    std::vector<Body> bodies;
};