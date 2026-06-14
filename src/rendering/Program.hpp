#pragma once

#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Program {
public:
    Program(std::string_view vertexFile, std::string_view fragmentFile) noexcept;
private:
    GLint id;

    GLuint CreateShader(std::string_view vertexShader, std::string_view fragmentShader);
    GLuint CompileShader(GLenum type, std::string_view source);
    void ShaderError(GLuint id);
};