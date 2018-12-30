#pragma once
#include <vector>
#include "model.h"


struct Scene
{
        void AddModel(model_t* model, transform_t transform);
        void AddModel(model_t* model);
        std::vector<model_t*> models;
};