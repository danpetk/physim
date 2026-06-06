#pragma once

#include <print>
#include <span>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "../physics/Body.hpp"

class Renderer {
public:
    Renderer();
    void DrawBodies(std::span<const Body> bodies);
private:
    VertexArray array;
    VertexBuffer buf;
    ElementBuffer elem;
};