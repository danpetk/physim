#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();
private:
    GLuint id;
};