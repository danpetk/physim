#pragma once

#include <span>
#include <vector>

#include "Body.hpp"

class Physics {
public:
    void AddBody(Shape shape, Vec2 position, double mass);
    std::span<const Body> GetBodies();
private:
    std::vector<Body> bodies;
};