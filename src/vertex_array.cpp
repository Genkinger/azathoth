#include "vertex_array.h"



VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_ID)); 
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_ID));    
}

void VertexArray::Bind()
{
    GLCall(glBindVertexArray(m_ID));
}

void VertexArray::Unbind()
{  
    GLCall(glBindVertexArray(0));
}

void VertexArray::EnableAttribArray(GLuint index)
{
    GLCall(glEnableVertexAttribArray(index));
}

void VertexArray::AttribPointer(GLuint index, GLuint size, GLenum type, GLenum normalized, GLuint stride, void* offset)
{
    GLCall(glVertexAttribPointer(index,size,type,normalized,stride,offset));
}
