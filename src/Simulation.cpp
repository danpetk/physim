#include "Simulation.hpp"

#include <array>
#include <cassert>
#include <thread>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

void Simulation::Run() {
    physics.AddShape(Box{{Vec2{0, 0}, 100}, 2, 2});

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        // physics.Update();
        renderer.DrawShapes(physics.GetShapes());

        glfwSwapBuffers(window);
    }
}

void Simulation::OnWindowResize(int width, int height) {
    renderer.ResizeView(width, height);
}

