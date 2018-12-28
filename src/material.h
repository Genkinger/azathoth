#pragma once
#include "common.h"
#include "texture.h"

#define AMS1_MAGIC "AMS1"
#define AMS1_TEXTURE_NONE "NONE"

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

struct ams1_material_t
{
    char        name[64];    
    float       ka[3];      //ambient
    float       kd[3];      //diffuse
    float       ks[3];      //specular
    float       ns;         //specular exponent (0 - 10)
    float       tr;         //transparency ( 1-d )
    int         illum;      //illumination model
    char        map_ka[64]; 
    char        map_kd[64];
    char        map_ks[64];
    char        map_ns[64];
    char        map_bump[64];
    char        map_disp[64];
    char        decal[64];
};

struct ams1_header_t
{   
    int8_t      magic[4];
    int32_t     num_materials;
};

struct ams1_t
{
    ams1_header_t header;
    ams1_material_t  *materials;
};

struct material_lib_t
{
    int32_t num_materials;
    material_t *materials;
};

material_lib_t az_ams1_material_load(const char* path);
material_t *az_internal_ams1_material_texture_load(ams1_t *ams1);
void        az_ams1_material_free(material_t *materials);