#include "Simulation.hpp"

#include <iostream>
#include <optional>

#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

#include <cassert>
#include<iostream>

// Forward Declaration
GLFWwindow* InitWindow();

int Simulation::Run() {
    physics.AddBody(Box{5, 5}, Vec2{10, 10}, 100);
   
    GLFWwindow* window;
    if (!(window = InitWindow())) {
        return -1;
    }
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.DrawBodies(physics.GetBodies());

        glfwSwapBuffers(window);
    }

    return 0;   
}

GLFWwindow* InitWindow() {
    GLFWwindow* window;
    
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialize";
        return nullptr;
    }

    window = glfwCreateWindow(1280, 720, "Physim", NULL, NULL);
    if (!window) {
        std::cerr << "Error creating window";
        glfwTerminate();
        return nullptr;
    }

    return window;
}