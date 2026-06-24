#version 430 core

layout(location = 0) in vec4 vertPosition;
layout(location = 1) in vec4 instancePosition;
layout(location = 2) in vec4 instanceScale;

uniform mat4 projection;

void main() {
    vec4 worldPos = vertPosition * instanceScale + vec4(instancePosition.xy, 0.0, 0.0);
    gl_Position = projection * worldPos;
}