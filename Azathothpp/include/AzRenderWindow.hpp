#pragma once
#include "AzRenderTarget.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "string/AzString.hpp"

namespace Az{
    class RenderWindow : public RenderTarget{
        private:
	        GLFWwindow *m_WindowHandle;
        public:
            RenderWindow(int width, int height, const std::string &title, bool fullscreen = false, bool vsync = false, int posx = 0 , int posy = 0);
            void SwapBuffers();
            double Update();
            bool ShouldClose();
            void Clear();
            void SetTitle(const std::string& title);
            double GetTime();
            GLFWwindow *GetWindowHandle();
            ~RenderWindow();
    };
}