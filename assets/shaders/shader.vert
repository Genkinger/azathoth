#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 2) in vec3 vertex_normal;
layout(location = 1) in vec2 vertex_uv;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 position;
out float cosTheta;
out float scale;

void main()
{
    vec3 lightPosition = vec3(0,3,0);
    vec4 pos = Model * vec4(vertex_position, 1);
    gl_Position = Projection * View * pos;
    position = vertex_position;
    cosTheta = clamp(dot(normalize(vertex_normal),(lightPosition-pos.xyz)),0,1);
    float len = length(lightPosition-pos.xyz);
    scale = 10/(len);
}   