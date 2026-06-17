#pragma once

#include "physics/Physics.hpp"
#include "rendering/Renderer.hpp"

class Simulation {
public:
    [[nodiscard]] int Run() const noexcept;
};