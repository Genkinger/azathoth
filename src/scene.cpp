#include "scene.h"


void Scene::AddModel(model_t* model, transform_t transform)
{
    //transform = transform;
    models.push_back(model);
}

void Scene::AddModel(model_t* model)
{
    models.push_back(model);
}
