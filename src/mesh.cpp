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

mesh_t az_mesh_load_aps2(const char* path,const char* name)
{
    mesh_t mesh;

    mesh.vbo = new VertexBuffer();
    mesh.aps2 = az_aps2_load(path);
    
    int floatcount = 0;
    aps2_group_t *group = NULL;
    for(int i = 0; i < mesh.aps2->header.num_groups; i++){
        if(!memcmp(name,mesh.aps2->groups[i].header.name,strlen(name))){
            group = &mesh.aps2->groups[i];
        }
    }
    if(!group)
    {
        printf("Couldn't find mesh named: %s\n",name);
        return mesh;
    }

    material_lib_t mtllib = az_ams1_material_load(mesh.aps2->header.mtllib);
    
    for(int i = 0; i < mtllib.num_materials; i++)
    {
        if(!strcmp(mtllib.materials[i].name,group->header.material)){
            mesh.material = mtllib.materials[i];
        }
    }

    float *data = (float*)malloc(sizeof(float)*group->header.num_faces*9*3*(3+2+3));

    for(int i = 0; i < group->header.num_faces; i++)
    {   
        data[i * 3 * (3+2+3) + 0 ] = mesh.aps2->v[group->faces[i].v_indices[0] * 3 + 0];
        data[i * 3 * (3+2+3) + 1 ] = mesh.aps2->v[group->faces[i].v_indices[0] * 3 + 1];
        data[i * 3 * (3+2+3) + 2 ] = mesh.aps2->v[group->faces[i].v_indices[0] * 3 + 2];

        data[i * 3 * (3+2+3) + 3 ] = mesh.aps2->v[group->faces[i].v_indices[1] * 3 + 0];
        data[i * 3 * (3+2+3) + 4 ] = mesh.aps2->v[group->faces[i].v_indices[1] * 3 + 1];
        data[i * 3 * (3+2+3) + 5 ] = mesh.aps2->v[group->faces[i].v_indices[1] * 3 + 2];

        data[i * 3 * (3+2+3) + 6 ] = mesh.aps2->v[group->faces[i].v_indices[2] * 3 + 0];
        data[i * 3 * (3+2+3) + 7 ] = mesh.aps2->v[group->faces[i].v_indices[2] * 3 + 1];
        data[i * 3 * (3+2+3) + 8 ] = mesh.aps2->v[group->faces[i].v_indices[2] * 3 + 2];


        data[i * 3 * (3+2+3) + 9  ] = mesh.aps2->vt[group->faces[i].vt_indices[0] * 2 + 0];
        data[i * 3 * (3+2+3) + 10 ] = mesh.aps2->vt[group->faces[i].vt_indices[0] * 2 + 1];

        data[i * 3 * (3+2+3) + 11 ] = mesh.aps2->vt[group->faces[i].vt_indices[1] * 2 + 0];
        data[i * 3 * (3+2+3) + 12 ] = mesh.aps2->vt[group->faces[i].vt_indices[1] * 2 + 1];

        data[i * 3 * (3+2+3) + 13 ] = mesh.aps2->vt[group->faces[i].vt_indices[2] * 2 + 0];
        data[i * 3 * (3+2+3) + 14 ] = mesh.aps2->vt[group->faces[i].vt_indices[2] * 2 + 1];


        data[i * 3 * (3+2+3) + 15 ] = mesh.aps2->vn[group->faces[i].vn_indices[0] * 3 + 0];
        data[i * 3 * (3+2+3) + 16 ] = mesh.aps2->vn[group->faces[i].vn_indices[0] * 3 + 1];
        data[i * 3 * (3+2+3) + 17 ] = mesh.aps2->vn[group->faces[i].vn_indices[0] * 3 + 2];

        data[i * 3 * (3+2+3) + 18 ] = mesh.aps2->vn[group->faces[i].vn_indices[1] * 3 + 0];
        data[i * 3 * (3+2+3) + 19 ] = mesh.aps2->vn[group->faces[i].vn_indices[1] * 3 + 1];
        data[i * 3 * (3+2+3) + 20 ] = mesh.aps2->vn[group->faces[i].vn_indices[1] * 3 + 2];

        data[i * 3 * (3+2+3) + 21 ] = mesh.aps2->vn[group->faces[i].vn_indices[2] * 3 + 0];
        data[i * 3 * (3+2+3) + 22 ] = mesh.aps2->vn[group->faces[i].vn_indices[2] * 3 + 1];
        data[i * 3 * (3+2+3) + 23 ] = mesh.aps2->vn[group->faces[i].vn_indices[2] * 3 + 2];
    }


    mesh.vao.Bind();
    mesh.vbo->Bind();
    
    mesh.vbo->Data(mesh.aps1->header.num_vertices * (3+2+3) * sizeof(float), data, GL_STATIC_DRAW);
    
    mesh.vao.EnableAttribArray(0);
    mesh.vao.EnableAttribArray(1);
    mesh.vao.EnableAttribArray(2);
    
    //LAYOUT
    int stride = sizeof(float) * (3 + 2 + 3);
    mesh.vao.AttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,0);//Positions
    mesh.vao.AttribPointer(1,2,GL_FLOAT,GL_FALSE,stride,(void*)(3 * sizeof(float))); //UVs
    mesh.vao.AttribPointer(2,3,GL_FLOAT,GL_FALSE,stride,(void*)(5 * sizeof(float))); //Normals
    
    mesh.count = group->header.num_faces * (3 + 2 + 3);
    return mesh;
}

void az_mesh_free(mesh_t *mesh)
{
    delete mesh->vbo;
    az_aps1_free(mesh->aps1);
}