#include "Renderer.hpp"

#include "../utils.hpp"
#include "VertexBufferLayout.hpp"

Renderer::Renderer(int width, int height) : boxProgram{"assets/test.vertex.shader", "assets/test.fragment.shader"}{
    boxMeshVbo.CreateNewBufferWithData<Vec2>(
        std::array<Vec2, 4>{
            Vec2{-0.5, -0.5}, Vec2{0.5, -0.5}, 
            Vec2{0.5, 0.5}, Vec2{-0.5, 0.5}
        }, GL_STATIC_DRAW);

    boxMeshEbo.CreateNewBufferWithData(std::array<GLuint, 6>{0, 1, 2, 2, 3, 0}, GL_STATIC_DRAW);

    boxInstanceVbo.CreateNewBuffer(100 * sizeof(InstanceData), GL_DYNAMIC_DRAW); //! < TEMP DO SOMETHING OTHER THAN 100
    
    VertexBufferLayout boxMeshLayout;
    boxMeshLayout.AddAttribute<double>(2); //< vertex position
    boxVao.BindVertexBuffer(boxMeshVbo, boxMeshLayout);

    VertexBufferLayout boxInstanceLayout;
    boxInstanceLayout.AddAttribute<double>(2); //< box pos
    boxInstanceLayout.AddAttribute<double>(2); //< box scale
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
    InstanceData instanceData{interpState.position, Vec2{box.width, box.height}};

    boxInstances.push_back(instanceData);
}