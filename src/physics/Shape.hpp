#pragma once

#include <array>
#include <cassert>
#include <optional>
#include <variant>

#include "Vec.hpp"

struct WorldState {
    Vec2<double> prevPosition;
    Vec2<double> position;
    double invMass = 0;
    Vec2<double> velocity;

    double prevAngle = -0.1;
    double angle = -0.1;
    double invMoment = 0;
    double angularVelocity = 0;
    
    int gravScale = 1;
};

struct Box {
    double width;
    double height;

    constexpr Box(double w, double h) noexcept : width{w}, height{h} {
        assert(width > 0);
        assert(height > 0);
    }

    std::array<Vec2<double>, 4> GetVertices(const WorldState& state) const noexcept;
    std::array<Vec2<double>, 2> GetNormalizedNormals(const WorldState& state) const noexcept;

    constexpr double ComputeMoment(double mass) const noexcept {
        return mass * (width*width + height*height) / 12.0;
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
    BodyBuilder& MakeBox(double width, double height);
    BodyBuilder& Position(Vec2<double> p) noexcept;
    BodyBuilder& InvMass(double im) noexcept;
    BodyBuilder& GravOpt(Gravity g) noexcept;
    Body build();
private:
    std::optional<Shape> shape;
    WorldState state;
};
