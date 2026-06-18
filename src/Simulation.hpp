#pragma once

#include "physics/Physics.hpp"
#include "rendering/Renderer.hpp"

class Simulation {
public:
    Simulation(GLFWwindow* w, int width, int height) : window{w}, renderer{width, height} {}
    void Run();
private:
    GLFWwindow* window;
    Physics physics;
    Renderer renderer;
};