#include "Renderer.hpp"

#include "VertexBufferLayout.hpp"

Renderer::Renderer() {

    VertexBufferLayout boxLayout;
    // Two double for x,y
    boxLayout.AddAttribute<double>(2);
    boxVao.BindVertexBuffer(boxVbo, boxLayout);
    boxVao.BindElementBuffer(boxEbo);
}

void Renderer::DrawShapes(std::span<const Shape> shapes) {
    // for (const auto& body: bodies) {
    //     std::visit([&] (const auto& shape) {
    //         // Draw(shape, body.position);
    //     }, body.shape);
    // }

    //! TEMPORARY UNDERNEATH
    verts[1] += 0.001;
    verts[3] += 0.001;
    verts[5] += 0.001;

    boxVbo.AllocNewBufferData<double>(verts);
    boxEbo.AllocNewBufferData(indexes);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

}