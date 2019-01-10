/**
 * @file ams.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief definitions for the Azathoth Material Specification v1 (AMS1)
 * @version 1.0
 * @date 2018-12-30
 * 
 * @copyright Copyright (c) 2018, Lukas Genkinger,
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND,
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED,
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE,
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR,
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES,
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;,
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND,
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT,
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS,
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those,
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the Azathoth project.
 * 
 */
#pragma once 
#include "common.h"

#define AMS1_MAGIC "AMS1"
#define AMS1_TEXTURE_NONE "\0"

typedef struct 
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
} ams1_material_t;

typedef struct 
{   
    int8_t      magic[4];
    int32_t     num_materials;
} ams1_header_t;

typedef struct 
{
    ams1_header_t header;
    ams1_material_t  *materials;
} ams1_t;


/**
 * @brief loads a ams1 file from disk.
 * 
 * @param path the path to the ams1 file to load.
 * @return ams1_t* a pointer to a newly populated ams1_t struct (free with az_ams1_free(...) only!).
 */
ams1_t  *az_ams1_load(const char* path);

/**
 * @brief writes a ams1 file to disk.
 * 
 * @param path the path to the new ams1 file.
 * @param ams1 pointer to ams1_t struct.
 */
void    az_ams1_write(const char* path,ams1_t *ams1);

/**
 * @brief frees a ams1_t struct that was previously loaded with az_ams1_load(...).
 * 
 * @param ams1 pointer to ams1_t struct.
 */
void    az_ams1_free(ams1_t* ams1);