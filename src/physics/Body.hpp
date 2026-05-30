#pragma once

#include "Shape.hpp"
#include "Vec.hpp"

class Body {
public:
    Body(Shape s, Vec2 p, double m) : shape{std::move(s)}, position{p}, mass{m} {}
private:
    double mass = 0;
    Vec2 position;
    Vec2 velocity;
    Shape shape;
};