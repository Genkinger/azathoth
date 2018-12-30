#pragma once

#include "common.h"
#include "mesh.h"

struct model_t
{
    int32_t num_meshes;
    material_lib_t *mtllib;
    mesh_t **meshes;
    transform_t transform;
};


model_t *az_model_aps2_load(const char* path);
model_t *az_model_aps1_load(const char* path);

void    az_model_free(model_t *model);

