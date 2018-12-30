#include "ams.h"


ams1_t *az_ams1_load(const char* path)
{
    ams1_t *ams1 = (ams1_t*)malloc(sizeof(ams1_t));
    FILE *file = fopen(path,"rb");
    fread(&ams1->header,sizeof(ams1_header_t),1,file);
    if(memcmp(AMS1_MAGIC,ams1->header.magic,strlen(AMS1_MAGIC)))
    {
        printf("[%s]: Invalid magic number (not a AMS1 file)...\n",__func__);
        return NULL;
    }
    ams1->materials = (ams1_material_t*)malloc(sizeof(ams1_material_t) * ams1->header.num_materials);
    
    for(int i = 0; i < ams1->header.num_materials; i++)
    {
        fread(&ams1->materials[i],sizeof(ams1_material_t),1,file);
    }
    return ams1;
}

void az_ams1_write(const char* path,ams1_t *ams1){
    FILE *file = fopen(path,"wb");

    fwrite(&ams1->header,sizeof(ams1_header_t),1,file);
    for(int i = 0; i < ams1->header.num_materials; i++){
        fwrite(&ams1->materials[i],sizeof(ams1_material_t),1,file);
    }
    
    
    fclose(file);
}

void az_ams1_free(ams1_t* ams1)
{
    free(ams1->materials);
    free(ams1);
}