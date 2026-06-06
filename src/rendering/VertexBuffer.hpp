#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind();
    void Unbind();
private:
    GLuint id;
};