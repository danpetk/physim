#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();
private:
    GLuint id;
};