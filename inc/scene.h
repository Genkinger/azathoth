#pragma once
#include <vector>
#include "model.h"
#include "light.h"

struct Scene
{
        void AddModel(model_t* model, transform_t transform);
        void AddModel(model_t* model);
        void AddLight(light_t* light);
        std::vector<model_t*> models;
        std::vector<light_t*> lights;
};