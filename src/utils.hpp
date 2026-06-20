#pragma once

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <type_traits>

inline constexpr int HEIGHT = 720;
inline constexpr int WIDTH = 1280;
inline constexpr int VIEWPORT_HEIGHT = 10;

namespace utils {

template <typename T, typename... Ts>
concept IsOneOf = (std::is_same_v<T, Ts> || ...);

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// Could add more if needed
template <typename T>
concept IsAttribType = IsOneOf<T, double, int>;

template <typename T>
concept Bindable = requires(T t) {
    t.Bind();
    t.Unbind();
};

template <Bindable T>
struct BindLock {
    BindLock(T& o) : obj{o} {
        obj.Bind();
    }
    ~BindLock() {
        obj.Unbind();
    }
private:
    T& obj;
};

template <IsAttribType T>
consteval inline GLenum TypeToGLType() noexcept {
    if constexpr (std::is_same_v<T, double>) {
        return GL_DOUBLE;
    } else {
        static_assert(false, "Unsupported type in TypeToGLType");
    }
    return {};
}

};