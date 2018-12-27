#pragma once
#include <string>
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include "log.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "transform.h"
#include "az_aps.h"

class Mesh
{
    public:
        Mesh(const std::string& meshPath);
        ~Mesh();
        void Bind();
        void Unbind();
        int  Count() { return m_Count; } 
        Transform& GetTransform() { return m_Transform; }
    private:
        GLuint m_ID;
        VertexBuffer *m_VBO;
        VertexArray m_VAO;
        Transform m_Transform;
        int m_Count;
        aps1_t *m_APS1;

};



