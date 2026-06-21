#pragma once

#include <array>
#include <cassert>
#include <optional>
#include <variant>

#include "Vec.hpp"

struct WorldState {
    Vec2 position;
    Vec2 prevPosition;
    Vec2 velocity;
    double invMass = 0;
    int gravScale = 1;
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

enum class Gravity {
    Static, 
    Dynamic
};

class BodyBuilder {
public:
    BodyBuilder& MakeBox(double width, double height) {
        shape = Box{width, height};
        return *this;
    }

    BodyBuilder& Position(Vec2 p) {
        state.position = p;
        return *this;
    }

    BodyBuilder& InvMass(double im) {
        state.invMass = im;
        return *this;
    }

    BodyBuilder& Gravity(Gravity g) {
        state.gravScale = (g == Gravity::Static ? 0 : 1);
        return *this;
    }

    Body build() {
        if (!shape) {
            std::terminate();
        }
        return Body{std::move(*shape), std::move(state)};
    }
private:
    std::optional<Shape> shape;
    WorldState state;
};
