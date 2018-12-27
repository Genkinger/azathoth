#pragma once
#include "farbfeld.h"

struct texture_t
{
    int32_t width;
    int32_t height;

    GLenum wrap_s;
    GLenum wrap_t;
    GLenum min_filter;
    GLenum mag_filter;

    GLuint id;

};

texture_t az_texture_farbfeld_load(const char* path, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT );
