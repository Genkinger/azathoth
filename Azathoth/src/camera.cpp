#include "camera.h"



Camera::Camera(Input& input, float aspect) : m_Input(input)
{
    view = glm::mat4(1);
    projection = glm::perspective(fovy, aspect, near, far);
}

void Camera::Update()
{

    if(m_Input.Buttons[GLFW_MOUSE_BUTTON_1])
    {
        auto pitchdelta = 1.f;
        auto delta = (m_Input.LastLeftDown-m_Input.CursorPosition);
        pitch   -= delta.y * factor;
        yaw     += delta.x * factor;
    }

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    direction = glm::normalize(direction);
    
    right = glm::normalize(glm::cross(direction, world_up));
    up = glm::normalize(glm::cross(direction,right));
    


    if(m_Input.Keys[GLFW_KEY_W]){
        position += direction * speed;
    }
    if(m_Input.Keys[GLFW_KEY_S]){
        position -= direction * speed;
    }
    if(m_Input.Keys[GLFW_KEY_A]){
        position -= right * speed;
    }
    if(m_Input.Keys[GLFW_KEY_D]){
        position += right * speed;
    }
    if(m_Input.Keys[GLFW_KEY_SPACE]){
        position += world_up * speed;
    }
    if(m_Input.Keys[GLFW_KEY_LEFT_CONTROL]){
        position -= world_up * speed;
    }

    view = glm::lookAt(position, position + direction, up);
}