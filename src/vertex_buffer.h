#pragma once
#include "common.h"
#include "gl_bindable.h"


class VertexBuffer : public GLBindable
{
    public:
        VertexBuffer();
        void Bind() override;
        void Unbind() override;
        void SetTarget(GLenum target);
        void SubData(GLintptr offset, GLsizeiptr size, const void* data);
        void Data(GLsizeiptr size, const void *data, GLenum usage);
        ~VertexBuffer();

    private:
        GLenum m_Target;
};