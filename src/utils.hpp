#pragma once

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <type_traits>

namespace utils {

template <typename T, typename... Ts>
concept IsOneOf = (std::is_same_v<T, Ts> || ...);

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