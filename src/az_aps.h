#pragma once
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define APS1_MAGIC  ('A' << 24 || 'P' << 16 || 'S' << 8 || '1')
#define APS2_MAGIC  ('A' << 24 || 'P' << 16 || 'S' << 8 || '2')


struct aps1_header_t
{   
    int8_t      magic[4];       // EMF_MAGIC "APS1"
    int32_t     num_vertices;
};

struct aps1_t
{
    aps1_header_t    header;
    float           *data;
};


struct aps2_header_t
{
    int8_t      magic[4];       // EMF2_MAGIC "APS2"
    
    int32_t     num_vertices;
    int32_t     num_st;
    int32_t     num_normals;
    int32_t     num_tris;

    int32_t     ofs_vertices;
    int32_t     ofs_st;
    int32_t     ofs_normals;
    int32_t     ofs_tris;

};

struct aps2_t {
    aps2_header_t    header;
};


aps1_t   *az_aps1_load(const char* path);
void    az_aps1_free(aps1_t *emf);


aps2_t  *az_aps2_load(const char* path);
void    az_aps2_free(aps2_t *emf2);

