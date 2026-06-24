#pragma once

#include <print>
#include <span>

#include "Program.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "../physics/Shape.hpp"

struct InstanceData {
    Vec2 position;
    Vec2 scale;
};

class Renderer {
public:
    Renderer(int width, int height);
    void DrawBodies(std::span<const Body> bodies, double alpha);
    void ResizeView(int width, int height);
private:
    VertexArray boxVao;
    VertexBuffer boxMeshVbo;
    ElementBuffer boxMeshEbo;

    VertexBuffer boxInstanceVbo;
    Program boxProgram;

    std::vector<InstanceData> boxInstances{};

    void HandleDrawShape(const Box& box, const WorldState& state, double alpha);
};