#version 330 core

layout (location = 3) out vec3 gPosition;
layout (location = 2) out vec3 gNormal;
layout (location = 0) out vec3 gColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 ST;

uniform sampler2D diffuse_texture;

void main()
{
    gPosition = FragPos;
    gNormal = normalize(Normal);
    gColor = texture(diffuse_texture,ST).rgb;
}