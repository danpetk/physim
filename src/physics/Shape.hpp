#pragma once

#include <variant>

struct Box {
    double width;
    double height;

    Box(double w, double h) : width{w}, height{h} {
        assert(width > 0);
        assert(height > 0);
    }
};

struct Circle {
    double radius = 0;

    Circle(double r) : radius{r} {
        assert(radius > 0);
    }
};

using Shape = std::variant<Box, Circle>;