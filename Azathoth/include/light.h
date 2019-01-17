/**
 * @file light.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief light representation
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