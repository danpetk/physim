#include "Simulation.hpp"

#include <array>
#include <cassert>
#include <thread>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

void Simulation::Run() {
    physics.AddShape(Box{{Vec2{0, 0}, 100}, 0.5, 0.5});

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        physics.Update();
        renderer.DrawShapes(physics.GetShapes());

        glfwSwapBuffers(window);
    }
}

