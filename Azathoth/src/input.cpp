#include "input.h"



Input::Input(Window& window)
{
    GLFWwindow* win = window.GetWindowHandle();
    glfwSetWindowUserPointer(win,this);
    glfwSetCursorPosCallback(win,Input::CursorPosCallback);
    glfwSetMouseButtonCallback(win,Input::MouseButtonCallback);
    glfwSetKeyCallback(win,Input::KeyCallback);
    glfwSetScrollCallback(win,Input::ScrollCallback);
}

Input::~Input()
{

}


void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS)
    {
        input->Keys[key] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        input->Keys[key] = false;
    }
}

void Input::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    input->CursorPosition = glm::vec2((float)xpos,(float)ypos);
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    if(action == GLFW_PRESS)
    {
        input->Buttons[button] = true;
        if(button == GLFW_MOUSE_BUTTON_1)
        {
            input->LastLeftDown = input->CursorPosition;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        input->Buttons[button] = false;  
        if(button == GLFW_MOUSE_BUTTON_1)
        {
            input->LastLeftUp = input->CursorPosition;            
        }      
    }
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto input = static_cast<Input*>(glfwGetWindowUserPointer(window));
    input->Scroll += glm::vec2(xoffset,yoffset);
}