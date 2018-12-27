#pragma once
#include <vector>
#include "mesh.h"


class Scene
{
    public:
        Scene();
        ~Scene();
        void AddMesh(Mesh& mesh);
    private:
        std::vector<Mesh> m_Meshes;
};