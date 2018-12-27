#pragma once
#pragma once
#include <GL/glew.h>



class GLBindable
{
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    protected:
        GLuint m_ID;
};