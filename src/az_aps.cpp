#include "az_aps.h"

aps1_t *az_aps1_load(const char* path)
{
    FILE *file;
    file = fopen(path,"rb");
    aps1_t *aps1 = (aps1_t*)malloc(sizeof(aps1_t));
    fread(&aps1->header,sizeof(aps1_header_t),1,file);

    if(strncmp((char*)aps1->header.magic,"APS1",4)){
        printf("[%s]: Invalid Magic Number (Not a valid ASP1 file)!\n", __func__);
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


aps2_t *az_emf2_load(const char* path)
{
    return NULL;
}

void az_aps2_free(aps2_t *aps2)
{

}

