#pragma once
#include "farbfeld.h"

struct texture_t
{
    int32_t width = -1;
    int32_t height = -1;

    GLenum wrap_s = GL_REPEAT;
    GLenum wrap_t = GL_REPEAT;
    GLenum min_filter = GL_NEAREST;
    GLenum mag_filter = GL_NEAREST;
    GLuint index = 0;
    GLuint id = 0;

};

texture_t az_texture_farbfeld_load(const char* path, GLuint index = 0, GLuint wrap_s = GL_REPEAT, GLuint wrap_t = GL_REPEAT);
