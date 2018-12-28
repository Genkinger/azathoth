#include "material.h"

//PARTIALLY FINISHED

material_lib_t *az_material_lib_ams1_load(const char* path)
{
    ams1_t* ams1;
    ams1 = az_ams1_load(path);

    material_lib_t *material = (material_lib_t*)malloc(sizeof(material_lib_t));
    material->num_materials = ams1->header.num_materials;
    material->materials = az_internal_ams1_material_texture_load(ams1);
    az_ams1_free(ams1);

    return material;
}

material_t *az_internal_ams1_material_texture_load(ams1_t *ams1){
    material_t *material = (material_t*)malloc(sizeof(material_t) * ams1->header.num_materials);
    
    for(int i = 0; i < ams1->header.num_materials; i++){
        texture_t map_ka, map_kd, map_ks, map_ns, map_bump, map_disp, decal;

        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].map_ka,strlen(AMS1_TEXTURE_NONE)))
            map_ka = az_texture_farbfeld_load(ams1->materials[i].map_ka);
        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].map_kd,strlen(AMS1_TEXTURE_NONE)))
            map_kd = az_texture_farbfeld_load(ams1->materials[i].map_kd);
        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].map_ks,strlen(AMS1_TEXTURE_NONE)))
            map_ks = az_texture_farbfeld_load(ams1->materials[i].map_ks);
        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].map_ns,strlen(AMS1_TEXTURE_NONE)))
            map_ns = az_texture_farbfeld_load(ams1->materials[i].map_ns);
        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].map_bump,strlen(AMS1_TEXTURE_NONE)))
            map_bump = az_texture_farbfeld_load(ams1->materials[i].map_bump);
        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].map_disp,strlen(AMS1_TEXTURE_NONE)))
            map_disp = az_texture_farbfeld_load(ams1->materials[i].map_disp);
        if(strncmp(AMS1_TEXTURE_NONE,ams1->materials[i].decal,strlen(AMS1_TEXTURE_NONE)))
            decal = az_texture_farbfeld_load(ams1->materials[i].decal);
        
        strncpy(material[i].name,ams1->materials[i].name,64);
        memcpy(material[i].ka, ams1->materials[i].ka, 3);
        memcpy(material[i].kd, ams1->materials[i].kd, 3);
        memcpy(material[i].ks, ams1->materials[i].ks, 3);
        material[i].ns = ams1->materials[i].ns;
        material[i].tr = ams1->materials[i].tr;
        material[i].illum = ams1->materials[i].illum;
        material[i].map_ka = map_ka;
        material[i].map_kd = map_kd;
        material[i].map_ks = map_ks;
        material[i].map_ns = map_ns;
        material[i].map_bump = map_bump;
        material[i].map_disp = map_disp;
        material[i].decal = decal;
    }

    return material;
}

void az_material_lib_ams1_free(material_lib_t *mtllib)
{
    free(mtllib->materials);
    free(mtllib);
}
