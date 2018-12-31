#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec3 vertex_normal;


out vec3 FragPos;
out vec2 ST;
out vec3 Normal;

uniform mat4 NormalMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;


void main()
{
    gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position,1));
    Normal  = (NormalMatrix * vec4(vertex_normal,0)).xyz;
    FragPos = (ModelMatrix * vec4(vertex_position,1)).xyz;
    ST = vec2(vertex_uv.x,1-vertex_uv.y);
}