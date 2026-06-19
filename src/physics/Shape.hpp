#pragma once

#include <array>
#include <cassert>
#include <variant>


#include "Vec.hpp"

struct WorldState {
    Vec2 position;
    Vec2 prevPosition;
    Vec2 velocity;
    double mass;
   
    constexpr WorldState(Vec2 p, Vec2 v, double m) noexcept : position{p}, velocity{v}, mass{m} {
        assert(mass > 0);
    }
};

struct Box {
    double width;
    double height;

    constexpr Box(double w, double h) noexcept : width{w}, height{h} {
        assert(width > 0);
        assert(height > 0);
    }

    std::array<Vec2, 4> GetVertices(const WorldState& state) const noexcept {
        double w2 = width / 2;
        double h2 = height / 2;
        return {
            state.position + Vec2{-w2, h2},
            state.position + Vec2{w2, h2},
            state.position + Vec2{-w2, -h2},
            state.position + Vec2{w2, -h2}
        };
    }
};

struct Circle {
    double radius = 0;

    Circle(double r) noexcept : radius{r} {
        assert(radius > 0);
    }
};

using Shape = std::variant<Box>;

struct Body {
public:
    Shape shape;
    WorldState state;
    constexpr Body(Shape s, WorldState ws) noexcept : shape{std::move(s)}, state{std::move(ws)} {}
};
