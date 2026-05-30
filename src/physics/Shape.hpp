#pragma once

#include <variant>

struct Box {
    double width;
    double height;

    Box(double w, double h) : width{w}, height{h} {}
};

struct Circle {
    double radius = 0;

    Circle(double r) : radius{r} {}
};

using Shape = std::variant<Box, Circle>;