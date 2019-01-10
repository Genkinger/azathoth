#include "mesh.h"
#include <unistd.h>

/*mesh_t az_mesh_load_aps1(const char* path)
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
*/
mesh_t *az_mesh_load_from_aps2(aps2_t *aps2, aps2_group_t *group)
{
    mesh_t *mesh = (mesh_t*)calloc(1,sizeof(mesh_t));
    strcpy(mesh->name,group->header.name);
    GLCall(glGenBuffers(1,&mesh->vbo));
    GLCall(glGenVertexArrays(1,&mesh->vao));

    int size = sizeof(float)*group->header.num_faces*9*3*(3+2+3);
    float *data = (float*)calloc(1,size);

    for(int i = 0; i < group->header.num_faces; i++)
    {   
        data[i * 3 * (3+2+3) + 0 ] = aps2->v[group->faces[i].v_indices[0] * 3 + 0];
        data[i * 3 * (3+2+3) + 1 ] = aps2->v[group->faces[i].v_indices[0] * 3 + 1];
        data[i * 3 * (3+2+3) + 2 ] = aps2->v[group->faces[i].v_indices[0] * 3 + 2];
        
        data[i * 3 * (3+2+3) + 3 ] = aps2->vt[group->faces[i].vt_indices[0] * 2 + 0];
        data[i * 3 * (3+2+3) + 4 ] = aps2->vt[group->faces[i].vt_indices[0] * 2 + 1];
        
        data[i * 3 * (3+2+3) + 5 ] = aps2->vn[group->faces[i].vn_indices[0] * 3 + 0];
        data[i * 3 * (3+2+3) + 6 ] = aps2->vn[group->faces[i].vn_indices[0] * 3 + 1];
        data[i * 3 * (3+2+3) + 7 ] = aps2->vn[group->faces[i].vn_indices[0] * 3 + 2];


        data[i * 3 * (3+2+3) + 8 ] = aps2->v[group->faces[i].v_indices[1] * 3 + 0];
        data[i * 3 * (3+2+3) + 9 ] = aps2->v[group->faces[i].v_indices[1] * 3 + 1];
        data[i * 3 * (3+2+3) + 10 ] = aps2->v[group->faces[i].v_indices[1] * 3 + 2];

        data[i * 3 * (3+2+3) + 11 ] = aps2->vt[group->faces[i].vt_indices[1] * 2 + 0];
        data[i * 3 * (3+2+3) + 12 ] = aps2->vt[group->faces[i].vt_indices[1] * 2 + 1];

        data[i * 3 * (3+2+3) + 13 ] = aps2->vn[group->faces[i].vn_indices[1] * 3 + 0];
        data[i * 3 * (3+2+3) + 14 ] = aps2->vn[group->faces[i].vn_indices[1] * 3 + 1];
        data[i * 3 * (3+2+3) + 15 ] = aps2->vn[group->faces[i].vn_indices[1] * 3 + 2];


        data[i * 3 * (3+2+3) + 16 ] = aps2->v[group->faces[i].v_indices[2] * 3 + 0];
        data[i * 3 * (3+2+3) + 17 ] = aps2->v[group->faces[i].v_indices[2] * 3 + 1];
        data[i * 3 * (3+2+3) + 18 ] = aps2->v[group->faces[i].v_indices[2] * 3 + 2];

        data[i * 3 * (3+2+3) + 19 ] = aps2->vt[group->faces[i].vt_indices[2] * 2 + 0];
        data[i * 3 * (3+2+3) + 20 ] = aps2->vt[group->faces[i].vt_indices[2] * 2 + 1];

        data[i * 3 * (3+2+3) + 21 ] = aps2->vn[group->faces[i].vn_indices[2] * 3 + 0];
        data[i * 3 * (3+2+3) + 22 ] = aps2->vn[group->faces[i].vn_indices[2] * 3 + 1];
        data[i * 3 * (3+2+3) + 23 ] = aps2->vn[group->faces[i].vn_indices[2] * 3 + 2];
    }


    GLCall(glBindVertexArray(mesh->vao));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,mesh->vbo));
    GLCall(glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glEnableVertexAttribArray(2));
    

    //LAYOUT
    int stride = sizeof(float) * (3 + 2 + 3);
    GLCall(glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,0));
    GLCall(glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,stride,(void*)(3 * sizeof(float))));
    GLCall(glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,stride,(void*)(5 * sizeof(float))));    
    mesh->count = group->header.num_faces * 3;
    mesh->transform.model = glm::mat4(1);

    return mesh;
}

void az_mesh_free(mesh_t *mesh)
{
    
}