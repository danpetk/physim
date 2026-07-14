#include "Renderer.hpp"

#include "../utils.hpp"
#include "VertexBufferLayout.hpp"

Renderer::Renderer(int width, int height) : boxProgram{"assets/test.vertex.shader", "assets/test.fragment.shader"}{
    boxMeshVbo.CreateNewBufferWithData<Vec2<float>>(
        std::array<Vec2<float>, 4>{
            Vec2{-0.5f, -0.5f}, Vec2{0.5f, -0.5f}, 
            Vec2{0.5f, 0.5f}, Vec2{-0.5f, 0.5f}
        }, GL_STATIC_DRAW);

    boxMeshEbo.CreateNewBufferWithData(std::array<GLuint, 6>{0, 1, 2, 2, 3, 0}, GL_STATIC_DRAW);

    boxInstanceVbo.CreateNewBuffer(100 * sizeof(InstanceData), GL_DYNAMIC_DRAW); //! < TEMP DO SOMETHING OTHER THAN 100
    
    VertexBufferLayout boxMeshLayout;
    boxMeshLayout.AddAttribute<float>(2); //< vertex position
    boxVao.BindVertexBuffer(boxMeshVbo, boxMeshLayout);

    VertexBufferLayout boxInstanceLayout;
    boxInstanceLayout.AddAttribute<float>(2); //< box pos
    boxInstanceLayout.AddAttribute<float>(1); //< rotation
    boxInstanceLayout.AddAttribute<float>(2); //< box scale
    boxVao.BindVertexBuffer(boxInstanceVbo, boxInstanceLayout, 1);

    boxVao.BindElementBuffer(boxMeshEbo);

    ResizeView(width, height);
}

void Renderer::DrawBodies(std::span<const Body> bodies, double alpha) {
    boxInstances.clear();

    for (const auto& body : bodies) {
        std::visit([&](const auto& shape){
            HandleDrawShape(shape, body.state, alpha);
        }, body.shape);
    }   

    boxInstanceVbo.BufferSubData<InstanceData>(boxInstances);
 
    //here
    glDrawElementsInstanced(
        GL_TRIANGLES,
        6, // 6 indices
        GL_UNSIGNED_INT,            
        nullptr,                    
        boxInstances.size()        
    );
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
    interpState.angle = state.prevAngle + alpha * (state.angle - state.prevAngle);

    InstanceData instanceData{
        static_cast<Vec2<float>>(interpState.position),
        static_cast<float>(interpState.angle),
        static_cast<Vec2<float>>(Vec2{box.width, box.height}) 
    };

    boxInstances.push_back(instanceData);
}