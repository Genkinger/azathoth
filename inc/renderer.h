#pragma once
#include "scene.h"
#include "shader.h"
#include "camera.h"


struct Renderer
{
    void DrawScene(Scene& scene, Shader &shader, Camera& camera);
};