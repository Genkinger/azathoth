/**
 * @file mesh.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief mesh representation
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
#include "transform.h"
#include "aps.h"
#include "material.h"

struct mesh_t
{
    char            name[64];
    material_t      material;
    GLuint          vbo;
    GLuint          vao;
    transform_t     transform;
    int             count;
    aps1_t          *aps1;
};


mesh_t az_mesh_load_aps1(const char* path);
mesh_t *az_mesh_load_from_aps2(aps2_t *aps2, aps2_group_t *group);

void az_mesh_free(mesh_t *mesh);



