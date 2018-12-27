#version 330 core


in vec3 position;
out vec4 color;
in float cosTheta;
in float scale;
void main()
{
    color = scale * cosTheta * vec4(1,1,1,1) + vec4(0.1,0.1,0.1,0.1);
}