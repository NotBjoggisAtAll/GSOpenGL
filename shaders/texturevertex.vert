#version 330 core

layout(location = 0) in vec4 VerticesPosition;
layout(location = 1) in vec4 VerticesNormals;
layout(location = 2) in vec2 VerticesUV;

out vec2 UV;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {
   UV = VerticesUV;
   gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * VerticesPosition;
}
