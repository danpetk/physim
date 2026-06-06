#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../utils.hpp"

using utils::IsAttribType;
using utils::TypeToGLType;

struct AttribInfo {
    GLint size;
    size_t offset;
    GLenum type;
    GLboolean normalized;
    AttribInfo(GLint s, size_t o, GLenum t, GLboolean n) : size{s}, offset{o}, type{t}, normalized{n} {};
};

class VertexBufferLayout {
public:
    template <IsAttribType T>
    void AddAttribute(GLint size) {
        attributes.emplace_back(size, static_cast<size_t>(stride), TypeToGLType<T>(), GL_FALSE);
        stride += sizeof(T) * size;
    }

    void SetAndEnableAttribPointers() const;
private:
    GLsizei stride = 0;
    std::vector<AttribInfo> attributes;
};