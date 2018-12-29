#pragma once
#include "common.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "transform.h"
#include "aps.h"
#include "material.h"

struct mesh_t
{
    char            name[64];
    material_t      material;
    GLuint          vbo;
    GLuint          vao;
    transform_t     transform;
    int             count;
    aps1_t          *aps1;
};


mesh_t az_mesh_load_aps1(const char* path);
mesh_t *az_mesh_load_from_aps2(aps2_t *aps2, aps2_group_t *group);

void az_mesh_free(mesh_t *mesh);



