#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include "log.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "transform.h"
#include "az_aps.h"
#include "texture.h"

struct mesh_t
{
    texture_t texture;
    VertexBuffer *vbo;
    VertexArray vao;
    transform_t transform;
    int count;
    aps1_t *aps1;
    aps2_t *aps2;
};


mesh_t az_mesh_load_aps1(const char* path);
void az_mesh_free(mesh_t *mesh);



