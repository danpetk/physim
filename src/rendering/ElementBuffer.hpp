#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ElementBuffer {
public:
    ElementBuffer();
    ~ElementBuffer();

    void Bind();
    void Unbind();
private:
    GLuint id;
};