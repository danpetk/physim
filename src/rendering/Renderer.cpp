#include "Renderer.hpp"

#include "../utils.hpp"
#include "VertexBufferLayout.hpp"

Renderer::Renderer(int width, int height) : boxProgram{"assets/test.vertex.shader", "assets/test.fragment.shader"}{

    boxVbo.CreateNewBuffer(100 * sizeof(Vec2), GL_DYNAMIC_DRAW); //! < TEMP DO SOMETHING OTHER THAN 100
    boxEbo.CreateNewBuffer(150 * sizeof(GLuint), GL_DYNAMIC_DRAW); //! < TEMP ABOVE

    VertexBufferLayout boxLayout;
    // Two double for x,y
    boxLayout.AddAttribute<double>(2);

    boxVao.BindVertexBuffer(boxVbo, boxLayout);
    boxVao.BindElementBuffer(boxEbo);

    ResizeView(width, height);
}

void Renderer::DrawBodies(std::span<const Body> bodies, double alpha) {

    currBoxInd = 0;
    boxIndices.clear();
    boxVerts.clear();

    for (const auto& body : bodies) {
        std::visit([&](const auto& shape){
            HandleDrawShape(shape, body.state, alpha);
        }, body.shape);
    }   

    boxVbo.BufferSubData<Vec2>(boxVerts);
    boxEbo.BufferSubData(boxIndices);
    // std::println("{}", boxVerts.size());
    // std::println("{}", boxIndices);
    glDrawElements(GL_TRIANGLES, boxIndices.size(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::ResizeView(int width, int height) {
    float windowRatio = (static_cast<float>(height) / width);
    float heightScaler = 2.0f / VIEWPORT_HEIGHT;
    std::array<float, 16> scaleProjection = {
        heightScaler * windowRatio, 0.0f, 0.0f, 0.0f,
        0.0f, heightScaler, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    boxProgram.Bind();
    auto loc = boxProgram.GetUniformLocation("projection");
    boxProgram.SetUniformMatrix4fv(loc, scaleProjection);
}


void Renderer::HandleDrawShape(const Box& box, const WorldState& state, double alpha) {
    WorldState interpState = state;
    interpState.position = state.prevPosition + alpha * (state.position - state.prevPosition);

    //! Temp below
    auto verts = box.GetVertices(interpState);
    boxVerts.insert(boxVerts.end(), verts.begin(), verts.end());
    boxIndices.push_back(currBoxInd++);
    auto a = currBoxInd++;
    auto b = currBoxInd++;
    boxIndices.insert(boxIndices.end(), {a,b,a,b});
    boxIndices.push_back(currBoxInd++);
}