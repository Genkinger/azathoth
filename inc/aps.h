/**
 * @file aps.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief definitions for the Azathoth Polygon Specification v1 and v2 (APS1|APS2).
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

#define APS1_MAGIC  "APS1"
#define APS2_MAGIC  "APS2"


typedef struct
{   
    int8_t      magic[4];       // APS_MAGIC "APS1"
    int32_t     num_vertices;
} aps1_header_t;

typedef struct
{
    aps1_header_t    header;
    float           *data;
} aps1_t;


/**
 * @brief loads an aps1 file from disk.
 * 
 * @param path 
 * @return aps1_t* (free with az_aps1_free() only!).
 */
aps1_t   *az_aps1_load(const char* path);

/**
 * @brief frees an aps1_t struct that was previously loaded by az_aps1_load().
 * 
 * @param aps1 
 */
void    az_aps1_free(aps1_t *aps1);

typedef struct
{
    int32_t v_indices[3];
    int32_t vn_indices[3];
    int32_t vt_indices[3];
} aps2_face_t;

typedef struct 
{
    char name[64];
    char material[64];
    int32_t num_faces;
} aps2_group_header_t;

typedef struct
{
    aps2_group_header_t header;
    aps2_face_t *faces;
} aps2_group_t;

typedef struct
{
    int8_t      magic[4];      // APS2_MAGIC "APS2"
    
    int32_t     num_groups;
    int32_t     num_v;
    int32_t     num_vn;
    int32_t     num_vt;

    char        mtllib[64];
} aps2_header_t;

typedef struct 
{
    aps2_header_t   header;
    float           *v;
    float           *vn;
    float           *vt;
    aps2_group_t    *groups;
} aps2_t;



/**
 * @brief loads an aps2 file from disk.
 * 
 * @param path the path to the file on disk.
 * @return aps2_t* a newly populated aps2_t struct (free with az_aps2_free() only!).
 */
aps2_t  *az_aps2_load(const char* path);

/**
 * @brief writes an aps2 file to disk.
 * 
 * @param path the path to the file on disk.
 * @param aps2 pointer to aps2_t struct.
 */
void    az_aps2_write(const char* path, aps2_t *aps2);

/**
 * @brief frees an aps2_t struct that was previously loaded by az_aps2_load().
 * 
 * @param aps2 pointer to aps2_t struct.
 */
void    az_aps2_free(aps2_t *aps2);

