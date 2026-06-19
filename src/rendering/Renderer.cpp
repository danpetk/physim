#include "Renderer.hpp"

#include "VertexBufferLayout.hpp"

Renderer::Renderer(int width, int height) : boxProgram{"assets/test.vertex.shader", "assets/test.fragment.shader"}{

    VertexBufferLayout boxLayout;
    // Two double for x,y
    boxLayout.AddAttribute<double>(2);
    boxVao.BindVertexBuffer(boxVbo, boxLayout);
    boxVao.BindElementBuffer(boxEbo);

    ResizeView(width, height);
}

void Renderer::DrawShapes(std::span<const Body> shapes) {
    // for (const auto& body: bodies) {
    //     std::visit([&] (const auto& shape) {
    //         // Draw(shape, body.position);
    //     }, body.shape);
    // }

    //! TEMPORARY UNDERNEATH
    
    auto box = std::get<Box>(shapes[0].shape);
    boxVbo.AllocNewBufferData<Vec2>(box.GetVertices(shapes[0].state));
    boxEbo.AllocNewBufferData(indexes);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void Renderer::ResizeView(int width, int height) {
    std::array<float, 16> scaleProjection = {
        (2.0f / Renderer::WORLD_HEIGHT) *(static_cast<float>(height) / width), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / Renderer::WORLD_HEIGHT, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    boxProgram.Bind();
    auto loc = boxProgram.GetUniformLocation("projection");
    boxProgram.SetUniformMatrix4fv(loc, scaleProjection);
}