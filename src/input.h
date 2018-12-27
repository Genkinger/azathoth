#pragma once
#include "window.h"
#include <glm/glm.hpp>



class Input
{
    public:
        Input(Window& window);
        ~Input();
    private:
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    public:
        bool Keys[65536];
        bool Buttons[65536];
        glm::vec2 CursorPosition;
        glm::vec2 LastLeftDown;
        glm::vec2 LastLeftUp;
        glm::vec2 Scroll;
};  