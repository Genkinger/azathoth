#version 330 core


in vec3 position;
out vec4 color;
in float cosTheta;
in float scale;
in vec2 st;
uniform sampler2D texture_sampler;

void main()
{
    vec4 col = texture(texture_sampler,st);
    color = scale * cosTheta * col + col * 0.3;
}