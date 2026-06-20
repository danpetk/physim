#include "Renderer.hpp"

#include "VertexBufferLayout.hpp"

Renderer::Renderer(int width, int height) : boxProgram{"assets/test.vertex.shader", "assets/test.fragment.shader"}{

    boxVbo.CreateNewBuffer(100, GL_DYNAMIC_DRAW);
    VertexBufferLayout boxLayout;
    // Two double for x,y
    boxLayout.AddAttribute<double>(2);

    boxVao.BindVertexBuffer(boxVbo, boxLayout);
    boxVao.BindElementBuffer(boxEbo);

    ResizeView(width, height);
    
    //! TEMP
    boxEbo.AllocNewBufferData(indexes);

}

void Renderer::DrawBodies(std::span<const Body> bodies, double alpha) {
    for (const auto& body : bodies) {
        std::visit([&](const auto& shape){
            HandleDrawShape(shape, body.state, alpha);
        }, body.shape);
    }   
}

void Renderer::ResizeView(int width, int height) {
    float windowRatio = (static_cast<float>(height) / width);
    float heightScaler = 2.0f / Renderer::WORLD_HEIGHT;
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

    boxVbo.BufferSubData<Vec2>(box.GetVertices(interpState));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}