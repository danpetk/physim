#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Simulation.hpp"

static constexpr int WIDTH = 720;
static constexpr int HEIGHT = 1280;

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id,
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
}

int main() {
    GLFWwindow* window;
    
    if (!glfwInit()) {
        std::println(stderr, "GLFW failed to initialize");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Physim", NULL, NULL);
    if (!window) {
        std::println(stderr, "Error creating window");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println(stderr, "Failed to initialize GLAD");
        glfwTerminate();
        return 1;
    }

    Simulation s{window, WIDTH, HEIGHT};       
    glfwSetWindowUserPointer(window, &s);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int w, int h) {
        glViewport(0, 0, w, h);
        Simulation* s = static_cast<Simulation*>(glfwGetWindowUserPointer(window));
        s->OnWindowResize(w, h);
    });

    s.Run();

    glfwDestroyWindow(window);
    glfwTerminate();
}