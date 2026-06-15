#include "Program.hpp"

#include <fstream>
#include <iostream>
#include <print>
#include <string>

void Program::Bind() const noexcept {
    glUseProgram(id);
}

void Program::Unbind() const noexcept {
    glUseProgram(0);
}

Program::Program(std::string_view vertexFile, std::string_view fragmentFile) {
    std::println(std::cerr, "Loading shader files: {} {}", vertexFile, fragmentFile);
    
    std::ifstream vertexShaderFile(std::string{vertexFile});
    std::ifstream fragmentShaderFile(std::string{fragmentFile});
    
    if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open()) {
        std::println(std::cerr, "Failed to open shader files");
        std::terminate();
    }

    std::string vertexShaderSource((std::istreambuf_iterator<char>(vertexShaderFile)),
                                   std::istreambuf_iterator<char>());
    std::string fragmentShaderSource((std::istreambuf_iterator<char>(fragmentShaderFile)),
                                     std::istreambuf_iterator<char>());

    id = CreateProgram(vertexShaderSource, fragmentShaderSource);
}

GLuint Program::CreateProgram(std::string_view vertexShader, std::string_view fragmentShader) {
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) { 
        ShaderError(program, true);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint Program::CompileShader(GLenum type, std::string_view source) {
    GLuint id = glCreateShader(type);

    const char* src = source.data();
    auto len = static_cast<GLint>(source.length());
    glShaderSource(id, 1, &src, &len);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        ShaderError(id, false);
    }

    return id;
}

void Program::ShaderError(GLuint id, bool program) {
    int length;
    if (program) {
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
    } else {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    }
    std::string message(length, '\0');
    if (program) {
        glGetProgramInfoLog(id, length, &length, message.data());
    } else {
        glGetShaderInfoLog(id, length, &length, message.data());
    }
    std::println(std::cerr, "SHADER ERROR: {}", message);
    glDeleteShader(id);
    // Terminate here for now since we don't have that many shaders
    // And if one fails theres not really a point in simulating
    std::terminate();
}