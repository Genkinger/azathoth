#version 330 core


in vec3 position;
out vec4 color;
in float cosTheta;
in float scale;
in vec2 st;

uniform sampler2D diffuse;
uniform sampler2D ambient;
uniform sampler2D specular;
uniform sampler2D bump;

void main()
{
    vec4 col = texture(diffuse,st);
    color = scale * cosTheta * col + texture(ambient,st);
}