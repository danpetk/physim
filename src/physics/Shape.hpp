#pragma once

#include <array>
#include <cassert>
#include <variant>


#include "Vec.hpp"

struct WorldState {
    Vec2 position;
    Vec2 velocity;
    double mass;
   
    constexpr WorldState(Vec2 p, double m) noexcept : position{p}, mass{m} {
        assert(mass > 0);
    }
};

struct Body {
public:
    WorldState state;
    constexpr Body(WorldState s) noexcept : state{std::move(s)} {}
};

struct Box : Body {
    double width;
    double height;

    constexpr Box(WorldState s, double w, double h) noexcept : Body(std::move(s)), width{w}, height{h} {
        assert(width > 0);
        assert(height > 0);
    }

    std::array<Vec2, 4> GetVertices() const noexcept {
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

struct Circle : Body {
    double radius = 0;

    Circle(WorldState s, double r) noexcept : Body(std::move(s)), radius{r} {
        assert(radius > 0);
    }
};

using Shape = std::variant<Box>;