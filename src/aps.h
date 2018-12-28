#pragma once
#include <inttypes.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#define APS1_MAGIC  "APS1"
#define APS2_MAGIC  "APS2"


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







struct aps2_face_t
{
    int32_t v_indices[3];
    int32_t vn_indices[3];
    int32_t vt_indices[3];
};

struct aps2_group_header_t
{
    char name[64];
    char material[64];
    int32_t num_faces;
};

struct aps2_group_t
{
    aps2_group_header_t header;
    aps2_face_t *faces;
};

struct aps2_header_t
{
    int8_t      magic[4];       // EMF2_MAGIC "APS2"
    
    int32_t     num_groups;
    int32_t     num_v;
    int32_t     num_vn;
    int32_t     num_vt;

    int32_t     ofs_groups;

    char        mtllib[64];
};

struct aps2_t {
    aps2_header_t   header;
    float           *v;
    float           *vn;
    float           *vt;
    aps2_group_t    *groups;
};


aps1_t   *az_aps1_load(const char* path);
void    az_aps1_free(aps1_t *emf);


aps2_t  *az_aps2_load(const char* path);
void    az_aps2_free(aps2_t *emf2);

