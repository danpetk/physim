#include "Simulation.hpp"

#include <array>
#include <cassert>
#include <thread>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

// void Simulation::Run() {
//     physics.AddBody(Box{5, 5}, {Vec2{0, 30}, 100});

//     while (!glfwWindowShouldClose(window)) {
//         glfwPollEvents();
//         glClear(GL_COLOR_BUFFER_BIT);

//         physics.Update(1.0/60);
//         renderer.DrawShapes(physics.GetBodies());

//         glfwSwapBuffers(window);
//     }
// }

void Simulation::Run() {
    physics.AddBody(Box{1, 1}, {Vec2{0, 4}, Vec2{0, 0}, 1.0/100});
    physics.AddBody(Box{1, 1}, {Vec2{-2, 5}, Vec2{0, 0}, 1.0/100});
    physics.AddBody(Box{2, 2}, {Vec2{4, 3}, Vec2{0, 0}, 1.0/100});

    constexpr double PHYSICS_DT = 1.0 / 60.0;
    double accumulator = 0.0;
    double prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double frameTime = currentTime - prevTime;
        prevTime = currentTime;
        if (frameTime > 0.25) frameTime = 0.25;
        accumulator += frameTime;

        glfwPollEvents();

        while (accumulator >= PHYSICS_DT) {
            physics.Update(PHYSICS_DT);
            accumulator -= PHYSICS_DT;
        }

        double alpha = accumulator / PHYSICS_DT;

        glClear(GL_COLOR_BUFFER_BIT);
        renderer.DrawBodies(physics.GetBodies(), alpha);
        glfwSwapBuffers(window);
    }
}

void Simulation::OnWindowResize(int width, int height) {
    renderer.ResizeView(width, height);
}

