#include "Simulation.hpp"

#include <array>
#include <cassert>
#include <thread>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

void Simulation::Run() {
    
    physics.AddBody(
        BodyBuilder{}.MakeBox(1.5, 0.25).Position({0, 5}).InvMass(1.0/100).build()
    );


    physics.AddBody(
        BodyBuilder{}.MakeBox(1, 3).Position({-3, 7}).InvMass(1.0/100).build()
    );

    physics.AddBody(
        BodyBuilder{}.MakeBox(2, 2).Position({4, 3}).InvMass(1.0/100).build()
    );

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

