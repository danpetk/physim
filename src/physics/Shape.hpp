#pragma once

#include <variant>

struct Circle {
    double radius = 0;

    Circle() = delete;
    Circle(double r) : radius{r} {}
};

using Shape = std::variant<Circle>;