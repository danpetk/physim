#pragma once

#include <span>
#include <vector>

#include "Shape.hpp"

class Physics {
public:
    void AddShape(Shape shape);
    [[nodiscard]] std::span<const Shape> GetShapes() const noexcept;
private: 
    std::vector<Shape> shapes;
};