#pragma once
#include "scene.h"
#include "shader.h"
#include "camera.h"


struct Renderer
{
    Renderer(int width, int height);
    void DrawSceneDeferred(Scene& scene, Camera& camera);
    void DrawSceneForward(Scene& scene, Camera& camera);
    void InitGBuffer(int width, int height);
    void InitQuad();
    void DrawFullscreenQuad();
    void DebugLightPass(Scene& scene, Camera& camera);
    void LightPass(Scene& scene, Camera& camera);
    void GeometryPass(Scene& scene, Camera& camera);

    Shader  *geometry;
    Shader  *lighting;
    Shader  *forward;

    GLuint  gBuffer;
    GLuint  textures[4];
    GLuint  depth_texture;

    GLuint  quad_vao;
    GLuint  quad_vbo;
    GLuint  attachments[4];

    int width;
    int height;
};