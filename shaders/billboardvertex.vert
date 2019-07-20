#version 330 core

layout(location = 0) in vec4 VerticesPosition;
layout(location = 1) in vec4 VerticesNormals;
layout(location = 2) in vec2 VerticesUV;

out vec2 UV;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec3 Position;
uniform vec3 Scale;

void main() {
   UV = VerticesUV;

   vec3 vertexPosition_worldspace = Position + vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]) * VerticesPosition.x * Scale.x + vec3(ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]) * VerticesPosition.y * Scale.y;

   gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertexPosition_worldspace, 1);
}
