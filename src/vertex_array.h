#pragma once
#include "common.h"
#include "gl_bindable.h"



class VertexArray : public GLBindable
{
    public:
        VertexArray();
        ~VertexArray();
        void EnableAttribArray(GLuint index);
        void AttribPointer(GLuint index, GLuint size, GLenum type, GLenum normalized, GLuint stride, void* offset);
        void Bind() override;
        void Unbind() override;
    private:

};