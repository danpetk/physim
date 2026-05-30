#pragma once

#include <cassert>

#include "Shape.hpp"
#include "Vec.hpp"

struct Body {
public:
    Shape shape;
    Vec2 position;
    Vec2 velocity;
    double mass = 0.0;
    
    Body(Shape s, Vec2 p, double m) : shape{std::move(s)}, position{p}, mass{m} {
        assert(mass > 0);
    }
};