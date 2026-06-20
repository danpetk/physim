#pragma once

#include <print>
#include <span>

#include "Program.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "../physics/Shape.hpp"

class Renderer {
public:
    Renderer(int width, int height);
    void DrawBodies(std::span<const Body> bodies, double alpha);
    void ResizeView(int width, int height);
private:
    static constexpr int WORLD_HEIGHT = 10;

    VertexArray boxVao;
    VertexBuffer boxVbo;
    ElementBuffer boxEbo;
    Program boxProgram;

    std::vector<unsigned int> indexes {0, 1, 2, 1, 2, 3};

    void HandleDrawShape(const Box& box, const WorldState& state, double alpha);
};