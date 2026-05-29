#pragma once

#include "Shape.hpp"
#include "Vec.hpp"

class Body {
public:

private:
    double mass = 0;
    Vec2 position;
    Vec2 velocity;
    Shape shape;
};