#version 330 core

layout(location = 0) in vec3 VerticesPosition;
layout(location = 1) in vec3 VerticesNormals;
layout(location = 2) in vec2 VerticesUV;

out vec3 Normals;
out vec3 FragPos;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {

   Normals = mat3(transpose(inverse(ModelMatrix))) * VerticesNormals;
   FragPos = vec3(ModelMatrix * vec4(VerticesPosition, 1));
   gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(VerticesPosition, 1);
}
