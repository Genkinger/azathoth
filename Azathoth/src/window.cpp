#include "window.h"



Window::Window(int width, int height, const std::string &title, bool fullscreen, bool vsync, int posx, int posy)
{
	if (!glfwInit()) {
		//LOG
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE,GL_TRUE);

	m_WindowHandle = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	glfwMakeContextCurrent(m_WindowHandle);
	
	if(vsync){
		glfwSwapInterval(1);
	}else{
		glfwSwapInterval(0);
	}

	if (glewInit() != GLEW_OK) {
		//LOG
	}

	glViewport(0, 0, width, height);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(m_WindowHandle);
}

double Window::Update() {
	glfwPollEvents();
	static double lastTime = GetTime();
	double currentTime = GetTime();
	double delta = currentTime - lastTime;
	lastTime = currentTime;
	return delta;
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(m_WindowHandle);
}

void Window::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SetTitle(const std::string& title){
	glfwSetWindowTitle(m_WindowHandle, title.c_str());
}

double Window::GetTime(){
	return glfwGetTime();
}

GLFWwindow *Window::GetWindowHandle() {
	return m_WindowHandle;
}

Window::~Window()
{
	glfwDestroyWindow(m_WindowHandle);
	glfwTerminate();
}
