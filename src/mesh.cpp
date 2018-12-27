#include "mesh.h"
#include <unistd.h>

Mesh::Mesh(const std::string& meshPath) : m_VAO(), m_VBO(new VertexBuffer())
{

    m_APS1 = az_aps1_load(meshPath.c_str());
    printf("MAGIC: %.*s, Size: %d\n",4,m_APS1->header.magic,m_APS1->header.num_vertices);

    m_VAO.Bind();
    m_VBO->Bind();
    
    m_VBO->Data(m_APS1->header.num_vertices * (3+2+3) * sizeof(float), m_APS1->data, GL_STATIC_DRAW);
    
    m_VAO.EnableAttribArray(0);
    m_VAO.EnableAttribArray(1);
    m_VAO.EnableAttribArray(2);
    
    //LAYOUT
    int stride = sizeof(float) * (3 + 2 + 3);
    m_VAO.AttribPointer(0,3,GL_FLOAT,GL_FALSE,stride,0);//Positions
    m_VAO.AttribPointer(1,2,GL_FLOAT,GL_FALSE,stride,(void*)(3 * sizeof(float))); //UVs
    m_VAO.AttribPointer(2,3,GL_FLOAT,GL_FALSE,stride,(void*)(5 * sizeof(float))); //Normals
    
    m_Count = m_APS1->header.num_vertices * (3 + 2 + 3);
}

Mesh::~Mesh()
{
    delete m_VBO;
    az_aps1_free(m_APS1);
}

void Mesh::Bind()
{
    m_VAO.Bind();
}

void Mesh::Unbind()
{
    m_VAO.Unbind();
}