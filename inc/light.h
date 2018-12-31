#pragma once
#include "common.h"

#define LIGHT_POINT 0
#define LIGHT_DIR 1
#define LIGHT_SPOT 2

typedef struct
{
    float   position[3];
    float   color[3];
    float   intensity = 1;
    int     type;
} light_t;

typedef struct 
{
    light_t     base;
    float       direction[3];
    
} light_directional_t;

typedef struct 
{
    light_t     base;
    float       kc = 1;
    float       kl = 1;
    float       kq = 1;
} light_point_t;

typedef struct 
{
    light_directional_t     base;
    float                   cutoff_inner;
    float                   cutoff_outer;
    float                   theta;
} light_spot_t;