#pragma once
#include "common.h"
#include <arpa/inet.h>

struct farbfeld_header_t
{
    int8_t      magic[8];
    uint32_t     width;
    uint32_t     height;
};

struct farbfeld_t
{
    farbfeld_header_t header;
    int16_t         *data;

};


farbfeld_t  *az_farbfeld_load(const char* path);
void        az_farbfeld_free(farbfeld_t *farbfeld);