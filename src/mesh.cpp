#include "mesh.h"
#include <unistd.h>

mesh_t az_mesh_load_aps1(const char* path)
{
    mesh_t mesh;

    mesh.vbo = new VertexBuffer();
    mesh.aps1 = az_aps1_load(path);

    mesh.vao.Bind();
    mesh.vbo->Bind();
    
    mesh.vbo->Data(mesh.aps1->header.num_vertices * (3+2+3) * sizeof(float), mesh.aps1->data, GL_STATIC_DRAW);
    
    mesh.vao.EnableAttribArray(0);
    mesh.vao.EnableAttribArray(1);
    mesh.vao.EnableAttribArray(2);
    
    //LAYOUT
    int stride = sizeof(float) * (3 + 2 + 3);
    mesh.vao.AttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,0);//Positions
    mesh.vao.AttribPointer(1,2,GL_FLOAT,GL_FALSE,stride,(void*)(3 * sizeof(float))); //UVs
    mesh.vao.AttribPointer(2,3,GL_FLOAT,GL_FALSE,stride,(void*)(5 * sizeof(float))); //Normals
    
    mesh.count = mesh.aps1->header.num_vertices * (3 + 2 + 3);
    return mesh;
}

void az_mesh_free(mesh_t *mesh)
{
    delete mesh->vbo;
    az_aps1_free(mesh->aps1);
}