#include "Physics.hpp"

void Physics::AddShape(Shape shape) {
    shapes.emplace_back(std::move(shape));
}

std::span<const Shape> Physics::GetShapes() const noexcept {
    return shapes;
}
