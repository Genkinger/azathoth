#pragma once 
#include "common.h"

#define AMS1_MAGIC "AMS1"
#define AMS1_TEXTURE_NONE "NONE"


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


ams1_t  *az_ams1_load(const char* path);
void    az_ams1_free(ams1_t* ams1);