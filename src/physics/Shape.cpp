#include "Shape.hpp"

std::array<Vec2<double>, 4> Box::GetVertices(const WorldState& state) const noexcept {
    double w2 = width / 2;
    double h2 = height / 2;
    return {
        state.position + Vec2{-w2, h2},
        state.position + Vec2{w2, h2},
        state.position + Vec2{-w2, -h2},
        state.position + Vec2{w2, -h2}
    };
}

std::array<Vec2<double>, 2> Box::GetNormalizedNormals(const WorldState& state) const noexcept {
    return {Vec2{0.0,1.0}, Vec2{1.0, 0.0}};
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
    return Body{std::move(*shape), std::move(state)};
}