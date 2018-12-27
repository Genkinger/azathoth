#pragma once
#include "common.h"
#include "texture.h"

#define AMS1_MAGIC "AMS1"

struct material_t
{
    char        name[64];
    glm::vec3   ka;         //ambient
    glm::vec3   kd;         //diffuse
    glm::vec3   ks;         //specular
    float       ns;         //specular exponent (0 - 10)
    float       tr;         //transparency ( 1-d )
    int         illum;      //illumination model
    texture_t   map_ka;      
    texture_t   map_kd;
    texture_t   map_ks;
    texture_t   map_ns;
    texture_t   map_bump;
    texture_t   map_disp;
    texture_t   map_decal;

};

struct ams1_material_t
{
    char        name[64];    
    glm::vec3   ka;         //ambient
    glm::vec3   kd;         //diffuse
    glm::vec3   ks;         //specular
    float       ns;         //specular exponent (0 - 10)
    float       tr;         //transparency ( 1-d )
    int         illum;      //illumination model
    char        map_ka[64]; 
    char        map_kd[64];
    char        map_ks[64];
    char        map_ns[64];
    char        map_bump[64];
    char        map_disp[64];
    char        map_decal[64];
};

struct ams1_header_t
{   
    int8_t      magic[4];
    int32_t     num_materials;
    int32_t     ofs_materials[16];
};

struct ams1_t
{
    ams1_header_t header;
    ams1_material_t  *materials;
};


material_t *az_ams1_material_load(const char* path);
void        az_ams1_material_free(material_t *materials);