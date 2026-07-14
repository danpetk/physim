#version 430 core

layout(location = 0) in vec4 vertPosition;
layout(location = 1) in vec4 instancePosition;
layout(location = 2) in float instanceRotation;
layout(location = 3) in vec4 instanceScale;

uniform mat4 projection;

void main() {
    vec4 relativeTransformation = vertPosition * instanceScale;

    mat2 rotation = mat2(
        cos(instanceRotation), -sin(instanceRotation),
        sin(instanceRotation),  cos(instanceRotation)
    );

    relativeTransformation.xy = rotation * relativeTransformation.xy;
    vec4 worldPos = relativeTransformation+ vec4(instancePosition.xy, 0.0, 0.0);
    gl_Position = projection * worldPos;
}