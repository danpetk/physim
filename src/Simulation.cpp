#include "Simulation.hpp"

#include <cassert>
#include <thread>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "physics/Shape.hpp"

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char *)alloca(length *sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


std::string vertextShader = 
    "#version 450 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "void main() {\n"
    "   gl_Position = position;\n"
    "}\n"
;

std::string fragmentShader = 
    "#version 450 core\n"
    "\n"
    "out vec4 color;\n"
    "\n"
    "void main() {\n"
    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n"
;



// Forward Declaration
GLFWwindow* InitWindow();

int Simulation::Run() const noexcept {
    Physics physics;
    physics.AddBody(Box{5, 5}, Vec2{10, 10}, 100);
    // physics.AddBody(Circle{5}, Vec2{10, 10}, 100);
   
    GLFWwindow* window;
    if (!(window = InitWindow())) {
        return -1;
    }

    {
        Renderer renderer;

        unsigned int shader = CreateShader(vertextShader, fragmentShader);
        glUseProgram(shader);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT);
    
            renderer.DrawBodies(physics.GetBodies());
            
    
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