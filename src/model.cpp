#include "model.h"

model_t *az_model_aps2_load(const char* path)
{
    model_t *model = (model_t*)calloc(1,sizeof(model_t));
    aps2_t *aps2 = az_aps2_load(path);
    material_lib_t *mtllib = az_material_lib_ams1_load(aps2->header.mtllib);
    model->mtllib = mtllib;

    model->num_meshes = aps2->header.num_groups;
    model->meshes = (mesh_t**)calloc(model->num_meshes,sizeof(mesh_t*));
    for(int i = 0; i < model->num_meshes; i++)
    {
        model->meshes[i] = az_mesh_load_from_aps2(aps2,&aps2->groups[i]);
        for(int j = 0; j < model->mtllib->num_materials; j++)
        {
            if(!strcmp(model->mtllib->materials[j].name,aps2->groups[i].header.material))
            {
                model->meshes[i]->material = model->mtllib->materials[j];
            }            
        }
    }
    
    return model;
}


//TODO: Incomplete
model_t *az_model_aps1_load(const char* path)
{
    //model_t *model = (model_t*)malloc(sizeof(model_t));
    //model->num_meshes = 1;
    //model->meshes[0] = (mesh_t*)malloc(sizeof(mesh_t));
    // model->meshes[0] = az_mesh_load_aps1(path);
    return NULL;
}



void az_model_free(model_t *model)
{
    for(int i = 0; i < model->num_meshes; i++){
        az_mesh_free(model->meshes[i]);
    }
    free(model->meshes);
    az_material_lib_ams1_free(model->mtllib);
    free(model);
}