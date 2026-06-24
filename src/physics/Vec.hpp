#pragma once

#include <concepts>
#include <format>

#include "../utils.hpp"

using utils::Numeric;

template <Numeric T>
struct Vec2 {
    T x = 0;
    T y = 0;

    Vec2 operator+(const Vec2& other) const noexcept {
        return {x + other.x, y + other.y};
    }

    Vec2& operator+=(const Vec2& other) noexcept{
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator-(const Vec2& other) const noexcept {
        return {x - other.x, y - other.y};
    }

    Vec2& operator-=(const Vec2& other) noexcept{
        x -= other.x;
        y -= other.y;
        return *this;
    }


    template <Numeric S>
    Vec2 operator*(S scalar) const noexcept{
        return {x * scalar, y * scalar};
    }

    
    template <Numeric S>
    Vec2& operator*=(S scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    
    template<typename U>
    explicit operator Vec2<U>() const {
        return { static_cast<U>(x), static_cast<U>(y) 
    };
}
};

template <Numeric T, Numeric S>
Vec2<T> operator*(S scalar, const Vec2<T>& other) {
    return other * scalar;
}

template<Numeric T>
struct std::formatter<Vec2<T>> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Vec2<T>& v, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", v.x, v.y);
    }
};