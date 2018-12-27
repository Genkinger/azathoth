#include "vertex_buffer.h"


VertexBuffer::VertexBuffer() : m_Target(GL_ARRAY_BUFFER)
{
    GLCall(glGenBuffers(1, &m_ID));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::Bind(){
    GLCall(glBindBuffer(m_Target,m_ID));
}

void VertexBuffer::Unbind()
{
    GLCall(glBindBuffer(m_Target,0));    
}

void VertexBuffer::SetTarget(GLenum target)
{
    m_Target = target;
}

void VertexBuffer::SubData(GLintptr offset, GLsizeiptr size, const void* data)
{
    GLCall(glBufferSubData(m_Target,offset,size,data));
}

void VertexBuffer::Data(GLsizeiptr size, const void* data, GLenum usage){
    GLCall(glBufferData(m_Target, size, data, usage));
}
