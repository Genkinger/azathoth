#pragma once
#include <vector>
#include "mesh.h"


struct Scene
{
        void AddMesh(mesh_t* mesh, transform_t transform);
        void AddMesh(mesh_t* mesh);
        std::vector<mesh_t*> meshes;
};