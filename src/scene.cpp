#include "scene.h"


void Scene::AddMesh(mesh_t* mesh, transform_t transform)
{
    mesh->transform = transform;
    meshes.push_back(mesh);
}

void Scene::AddMesh(mesh_t* mesh)
{
    meshes.push_back(mesh);
}