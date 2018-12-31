/**
 * @file farbfeld.h
 * @author Lukas Genkinger (genkinger@protonmail.com)
 * @brief farbfeld file format loader
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
#include <arpa/inet.h>

#define FF_MAGIC "farbfeld"

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

/**
 * @brief loads a farbfeld image from disk
 * 
 * @param path 
 * @return farbfeld_t* 
 */
farbfeld_t  *az_farbfeld_load(const char* path);
void        az_farbfeld_free(farbfeld_t *farbfeld);