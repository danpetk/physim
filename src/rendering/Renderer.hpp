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
    Renderer();
    void DrawShapes(std::span<const Shape> bodies);
private:
    VertexArray boxVao;
    VertexBuffer boxVbo;
    ElementBuffer boxEbo;
    Program boxProgram;

    std::vector<double> verts {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5}; 
    std::vector<unsigned int> indexes {0, 1, 2};

};