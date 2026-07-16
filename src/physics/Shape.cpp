#include <cmath>

#include "Shape.hpp"

std::array<Vec2<double>, 4> Box::GetVertices(const WorldState& state) const noexcept {
    double w2 = width / 2;
    double h2 = height / 2;

    auto axes = GetNormalizedNormals(state);
    Vec2<double> axisX = axes[0]; 
    Vec2<double> axisY = axes[1];

    return {
        state.position + axisX * -w2 + axisY *  h2,
        state.position + axisX *  w2 + axisY *  h2,
        state.position + axisX * -w2 + axisY * -h2,
        state.position + axisX *  w2 + axisY * -h2
    };
}       

std::array<Vec2<double>, 2> Box::GetNormalizedNormals(const WorldState& state) const noexcept {
    return {
        Vec2{std::cos(state.angle), std::sin(state.angle)},
        Vec2{-std::sin(state.angle), std::cos(state.angle)}
    };
}

BodyBuilder& BodyBuilder::MakeBox(double width, double height) {
        shape = Box{width, height};
        return *this;
    }

BodyBuilder& BodyBuilder::Position(Vec2<double> p) noexcept {
    state.position = p;
    return *this;
}

BodyBuilder& BodyBuilder::InvMass(double im) noexcept {
    assert(im >= 0);
    state.invMass = im;
    return *this;
}

BodyBuilder& BodyBuilder::GravOpt(Gravity g) noexcept {
    state.gravScale = (g == Gravity::Static ? 0 : 1);
    return *this;
}

Body BodyBuilder::build() {
    if (!shape) {
        std::terminate();
    }

    if (state.invMass > 0) {
        double mass = 1.0 / state.invMass;
        double moment = std::visit([mass](const auto& s) {
            return s.ComputeMoment(mass);
        }, *shape); 
        state.invMoment = 1.0 / moment;
    }

    return Body{std::move(*shape), std::move(state)};
}