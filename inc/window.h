#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window
{
private:
	GLFWwindow *m_WindowHandle;
public:
	Window(int width, int height, const std::string &title, bool fullscreen = false, bool vsync = false, int posx = 0 , int posy = 0);
	void SwapBuffers();
	double Update();
	bool ShouldClose();
	void Clear();
	void SetTitle(const std::string& title);
	double GetTime();
	GLFWwindow *GetWindowHandle();
	~Window();
};

