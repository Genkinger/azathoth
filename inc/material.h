/**
 * @file material.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief material representation
 * @version 1.0
 * @date 2018-12-31
 * 
 * @copyright Copyright (c) 2018, Lukas Genkinger
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