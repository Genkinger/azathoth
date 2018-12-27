#include "material.h"

//PARTIALLY FINISHED

material_t *az_ams1_material_load(const char* path)
{
    ams1_t ams1;
    FILE *file = fopen(path,"rb");
    fread(&ams1.header,sizeof(ams1_header_t),1,file);
    if(memcmp(AMS1_MAGIC,ams1.header.magic,strlen(AMS1_MAGIC)))
    {
        printf("[%s]: Invalid magic number (not a AMS1 file)...\n",__func__);
        return NULL;
    }
    for(int i = 0; i < ams1.header.num_materials; i++)
    {
        fseek(file,ams1.header.ofs_materials[i],0);
        ams1_material_t ams1_material;
        fread(&ams1_material,sizeof(ams1_material_t),1,file);
    }
    return NULL;
}

void az_ams1_material_free(material_t *materials)
{
    
}
