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
    
    constexpr Body(Shape s, Vec2 p, double m) noexcept : shape{std::move(s)}, position{p}, mass{m} {
        assert(mass > 0);
    }
};