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
    material_t *material = (material_t*)calloc(ams1->header.num_materials,sizeof(material_t));
    
    for(int i = 0; i < ams1->header.num_materials; i++){
        texture_t map_ka, map_kd, map_ks, map_ns, map_bump, map_disp, decal;

        if(ams1->materials[i].map_ka[0])
            map_ka = az_texture_farbfeld_load(ams1->materials[i].map_ka,1);
        if(ams1->materials[i].map_kd[0])
            map_kd = az_texture_farbfeld_load(ams1->materials[i].map_kd,0);
        if(ams1->materials[i].map_ks[0])
            map_ks = az_texture_farbfeld_load(ams1->materials[i].map_ks,2);
        if(ams1->materials[i].map_ns[0])
            map_ns = az_texture_farbfeld_load(ams1->materials[i].map_ns,4);
        if(ams1->materials[i].map_bump[0])
            map_bump = az_texture_farbfeld_load(ams1->materials[i].map_bump,3);
        if(ams1->materials[i].map_disp[0])
            map_disp = az_texture_farbfeld_load(ams1->materials[i].map_disp,5);
        if(ams1->materials[i].decal[0])
            decal = az_texture_farbfeld_load(ams1->materials[i].decal,6);
        
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
