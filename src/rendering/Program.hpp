#pragma once

#include <span>
#include <string>
#include <string_view>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Program {
public:
    Program(std::string_view vertexFile, std::string_view fragmentFile);
    void Bind() const noexcept;
    void Unbind() const noexcept;

    GLint GetUniformLocation(std::string_view name) noexcept;
    void SetUniformMatrix4fv(GLint location, std::span<const float, 16> value) const noexcept;
private:
    GLint id;
    std::unordered_map<std::string, GLint> uniformLocations;    

    GLuint CreateProgram(std::string_view vertexShader, std::string_view fragmentShader);
    GLuint CompileShader(GLenum type, std::string_view source);
    void ShaderError(GLuint id, bool program);
};