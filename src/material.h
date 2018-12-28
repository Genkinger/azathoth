#pragma once
#include "common.h"
#include "texture.h"
#include "ams.h"



struct material_t
{
    char        name[64];
    float       ka[3];      //ambient
    float       kd[3];      //diffuse
    float       ks[3];      //specular
    float       ns;         //specular exponent (0 - 10)
    float       tr;         //transparency ( 1-d )
    int         illum;      //illumination model
    texture_t   map_ka;      
    texture_t   map_kd;
    texture_t   map_ks;
    texture_t   map_ns;
    texture_t   map_bump;
    texture_t   map_disp;
    texture_t   decal;

};

struct material_lib_t
{
    int32_t num_materials;
    material_t *materials;
};

material_lib_t *az_material_lib_ams1_load(const char* path);
material_t *az_internal_ams1_material_texture_load(ams1_t *ams1);
void        az_material_lib_ams1_free(material_lib_t *materials);