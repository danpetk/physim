#include "Program.hpp"

#include <iostream>
#include <print>
#include <string>

Program::Program(std::string_view vertexFile, std::string_view fragmentFile) {

}

GLuint Program::CreateShader(std::string_view vertexShader, std::string_view fragmentShader) {
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) { // todo fix this
        ShaderError(id);
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
        ShaderError(id);
    }

    return id;
}

void Program::ShaderError(GLuint id) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    std::string message(length, '\0');
    glGetShaderInfoLog(id, length, &length, message.data());
    std::println(std::cerr, "SHADER ERROR: {}", message);
    glDeleteShader(id);
    // Terminate here for now since we don't have that many shaders
    // And if one fails theres not really a point in simulating
    std::terminate();
}