#pragma once
#include "input.h"
#include <glm/gtx/transform.hpp>



struct Camera
{
        
        glm::mat4 view;
        glm::mat4 projection;

        float pitch = 0; 
        float yaw = 0;
        float roll = 0;

        glm::vec3 up = glm::vec3(0.f,1.f,0.f);
        glm::vec3 world_up = glm::vec3(0.f,1.f,0.f);
        glm::vec3 right = glm::vec3(1.f,0.f,0.f);
        glm::vec3 direction = glm::vec3(0.f,0.f,-1.f);

        glm::vec3 position = glm::vec3(0.f,5.f,0.f);

        float fovy = 80.f;
        float near = 1.f;
        float far = 5000.f;

        float factor = 0.005f;
        float speed = 5.f;

        Camera(Input& input, float aspect);
        void Update();

    private:
        Input &m_Input;
};