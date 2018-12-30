#include "texture.h"


texture_t az_texture_farbfeld_load(const char* path, GLuint index, GLuint wrap_s, GLuint wrap_t)
{
    texture_t texture;
    texture.wrap_s = wrap_s;
    texture.wrap_t = wrap_t;
    texture.min_filter = GL_NEAREST;
    texture.mag_filter = GL_NEAREST;
    texture.index = index;

    GLCall(glGenTextures(1,&texture.id));
    GLCall(glActiveTexture(GL_TEXTURE0+texture.index));
    GLCall(glBindTexture(GL_TEXTURE_2D,texture.id));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,texture.wrap_s));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,texture.wrap_t));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,texture.min_filter));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,texture.mag_filter));

    farbfeld_t *image = az_farbfeld_load(path);
    
    texture.width = image->header.width;
    texture.height = image->header.height;

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_SHORT, image->data));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    az_farbfeld_free(image);

    return texture;
}