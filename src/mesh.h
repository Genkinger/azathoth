#pragma once
#include "common.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "transform.h"
#include "aps.h"
#include "material.h"

struct mesh_t
{
    material_t material;
    VertexBuffer *vbo;
    VertexArray vao;
    transform_t transform;
    int count;
    aps1_t *aps1;
    aps2_t *aps2;
};


mesh_t az_mesh_load_aps1(const char* path);
mesh_t az_mesh_load_aps2(const char* path, const char* name);

void az_mesh_free(mesh_t *mesh);



