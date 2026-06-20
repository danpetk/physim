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
    VertexArray boxVao;
    VertexBuffer boxVbo;
    ElementBuffer boxEbo;
    Program boxProgram;

    std::vector<Vec2> boxVerts{};
    std::vector<GLuint> boxIndices{};
    GLuint currBoxInd = 0;

    void HandleDrawShape(const Box& box, const WorldState& state, double alpha);
};