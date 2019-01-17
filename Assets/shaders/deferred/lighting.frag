#version 330 core

uniform sampler2D normal_texture;
uniform sampler2D color_texture;
uniform sampler2D position_texture;


vec2 CalcTexCoord()
{
   return gl_FragCoord.xy / vec2(800,600);
} 

in vec2 st;
out vec4 color;

void main()
{
    vec3 light = vec3(1,1,1);
    color = texture(color_texture,CalcTexCoord());
}