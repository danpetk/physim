#pragma once

#include "physics/Physics.hpp"
#include "rendering/Renderer.hpp"

class Simulation {
public:
    int Run();
private:
    Physics physics;
    Renderer renderer;
};