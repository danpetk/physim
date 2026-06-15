#include "Simulation.hpp"

#include <cassert>
#include <thread>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

// Forward Declaration
GLFWwindow* InitWindow();

int Simulation::Run() const noexcept {
    Physics physics;
    physics.AddShape(Box{{Vec2{10, 10}, 100}, 5, 5});
    // physics.AddBody(Circle{5}, Vec2{10, 10}, 100);
   
    GLFWwindow* window;
    if (!(window = InitWindow())) {
        return -1;
    }

    {
        Renderer renderer;

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT);
    
            physics.Update();
            renderer.DrawShapes(physics.GetShapes());
            
            glfwSwapBuffers(window);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;   
}

GLFWwindow* InitWindow() {
    GLFWwindow* window;
    
    if (!glfwInit()) {
        std::println(stderr, "GLFW failed to initialize");
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Physim", NULL, NULL);
    if (!window) {
        std::println(stderr, "Error creating window");
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println(stderr, "Failed to initialize GLAD");
        glfwTerminate();
        return nullptr;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
                            GLenum severity, GLsizei length,
                            const GLchar* message, const void* userParam)
    {
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
            return;
        }
        std::println(stderr, "GL: {}", message);
        if (type == GL_DEBUG_TYPE_ERROR) {
            std::terminate();
        }    
    }, nullptr);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
    });

    return window;
}