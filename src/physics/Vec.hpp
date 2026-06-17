#pragma once

#include <format>

struct Vec2 {
    double x = 0;
    double y = 0;

    Vec2 operator+(const Vec2& other) const noexcept {
        return {x + other.x, y + other.y};
    }

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

template<>
struct std::formatter<Vec2> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Vec2& v, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", v.x, v.y);
    }
};