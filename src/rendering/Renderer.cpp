#include "Renderer.hpp"

#include "VertexBufferLayout.hpp"

Renderer::Renderer(int width, int height) : boxProgram{"assets/test.vertex.shader", "assets/test.fragment.shader"}{

    VertexBufferLayout boxLayout;
    // Two double for x,y
    boxLayout.AddAttribute<double>(2);
    boxVao.BindVertexBuffer(boxVbo, boxLayout);
    boxVao.BindElementBuffer(boxEbo);

    std::array<float, 16> scaleProjection = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    boxProgram.Bind();
    auto loc = boxProgram.GetUniformLocation("projection");
    boxProgram.SetUniformMatrix4fv(loc, scaleProjection);
}

void Renderer::DrawShapes(std::span<const Shape> shapes) {
    // for (const auto& body: bodies) {
    //     std::visit([&] (const auto& shape) {
    //         // Draw(shape, body.position);
    //     }, body.shape);
    // }

    //! TEMPORARY UNDERNEATH
    
    auto box = std::get<Box>(shapes[0]);
    boxVbo.AllocNewBufferData<Vec2>(box.GetVertices());
    boxEbo.AllocNewBufferData(indexes);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}