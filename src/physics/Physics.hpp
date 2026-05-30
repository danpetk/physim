#pragma once

#include <vector>

#include "Body.hpp"

class Physics {
public:
    void AddBody(Shape shape, Vec2 position, double mass);
private:
    std::vector<Body> bodies;
};