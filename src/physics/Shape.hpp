#pragma once

#include <variant>

struct Box {
    double width;
    double height;

    constexpr Box(double w, double h) noexcept : width{w}, height{h} {
        assert(width > 0);
        assert(height > 0);
    }
};

struct Circle {
    double radius = 0;

    Circle(double r) noexcept : radius{r} {
        assert(radius > 0);
    }
};

using Shape = std::variant<Box, Circle>;