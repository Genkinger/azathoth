#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 2) in vec3 vertex_normal;
layout(location = 1) in vec2 vertex_uv;

uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

out float cosTheta;
out float scale;
out vec2 st;
out vec3 specular_col;

void main()
{
    vec4 vertex_pos = vec4(vertex_position,1);
    vec4 pos = ModelMatrix * vertex_pos;
    vec4 normal = NormalMatrix * vec4(vertex_normal,0);
    st = vec2(vertex_uv.x,1-vertex_uv.y);
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vertex_pos;

    vec3 lightDir = lightPosition-pos.xyz;
    vec3 viewDir = normalize(cameraPosition - pos.xyz);
    vec3 reflectDir = reflect(lightDir,normal.xyz);

    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    specular_col = 0.5 * spec * vec3(1,1,1);

    cosTheta = clamp(dot(normalize(normal.xyz),lightDir),0,1);
    float len = length(lightPosition-pos.xyz);
    scale = clamp(250000/(len * len),0,1);
}   