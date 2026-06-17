#include "Physics.hpp"

void Physics::Update() {
    for (auto& shape : shapes) {
        std::get<Box>(shape).state.position += {0.01, 0.01};
    }
}

void Physics::AddShape(Shape shape) {
    shapes.emplace_back(std::move(shape));
}

std::span<const Shape> Physics::GetShapes() const noexcept {
    return shapes;
}
