#version 330 core

out vec4 color;
in float cosTheta;
in float scale;
in vec2 st;
in vec3 specular_col;

uniform sampler2D diffuse_texture;
uniform sampler2D ambient_texture;
uniform sampler2D specular;
uniform sampler2D bump;

void main()
{
    vec4 diffuse_color = texture(diffuse_texture,st);
    vec4 ambient_color = texture(ambient_texture,st);
    color = scale * cosTheta * diffuse_color + ambient_color;// + vec4(specular_col,1.0);
}