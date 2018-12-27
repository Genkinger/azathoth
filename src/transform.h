#pragma once
#include <glm/glm.hpp>



struct Transform
{
    glm::vec3 translation = glm::vec3(0,0,0);
    glm::vec3 scale = glm::vec3(1,1,1);
    glm::mat4 model = glm::mat4(1);
};