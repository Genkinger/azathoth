#include "aps.h"

aps1_t *az_aps1_load(const char* path)
{
    FILE *file;
    file = fopen(path,"rb");
    aps1_t *aps1 = (aps1_t*)malloc(sizeof(aps1_t));
    fread(&aps1->header,sizeof(aps1_header_t),1,file);

    if(strncmp((char*)aps1->header.magic,APS1_MAGIC,4)){
        printf("[%s]: Invalid Magic Number (Not a valid APS1 file)!\n", __func__);
        return NULL;
    }

    aps1->data = (float*)malloc(sizeof(float) * aps1->header.num_vertices * (3+2+3));
    int result = fread(aps1->data,sizeof(float)*(3+2+3), aps1->header.num_vertices, file);
    
    fclose(file);
    return aps1;
}

void az_aps1_free(aps1_t *aps1)
{
    free(aps1->data);
    free(aps1);
}


aps2_t *az_aps2_load(const char* path)
{
    aps2_t *aps2 = (aps2_t*)malloc(sizeof(aps2_t));
    
    FILE *file = fopen(path,"rb");

    fread(&aps2->header,sizeof(aps2_header_t),1,file);
    
    if(memcmp(APS2_MAGIC,aps2->header.magic,strlen(APS2_MAGIC))){
        printf("Invalid magic number (not a APS2 file)...\n");
        return NULL;
    }
    int v_size = sizeof(float) * 3 * aps2->header.num_v;
    int vn_size = sizeof(float) * 3 * aps2->header.num_vn;
    int vt_size = sizeof(float) * 2 * aps2->header.num_vt;
    aps2->v = (float*)malloc(v_size);
    aps2->vn = (float*)malloc(vn_size);
    aps2->vt = (float*)malloc(vt_size);
    aps2->groups = (aps2_group_t*)malloc(sizeof(aps2_group_t)*aps2->header.num_groups);
    fread(aps2->v,v_size,1,file);
    fread(aps2->vn,vn_size,1,file);
    fread(aps2->vt,vt_size,1,file);

    //TODO: something isnt right here

    for(int i = 0; i < aps2->header.num_groups; i++)
    {
        aps2_group_t group;
        fread(&group.header,sizeof(aps2_group_header_t),1,file);
        group.faces = (aps2_face_t*)malloc(sizeof(aps2_face_t)*group.header.num_faces);
        fread(group.faces,sizeof(aps2_face_t)*group.header.num_faces,1,file);
        memcpy(&aps2->groups[i],&group,sizeof(aps2_group_t));
    }

    return aps2;
}

void az_aps2_free(aps2_t *aps2)
{

}

