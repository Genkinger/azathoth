
#include "AzRenderWindow.hpp"

namespace Az{
    RenderWindow::RenderWindow(int width, int height, const String &title, bool fullscreen, bool vsync, int posx, int posy)
    : RenderTarget(width,height){
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

        if(!gladLoadGL()){
            //TODO: log sth
        }

        glViewport(0, 0, width, height);
    }

    void RenderWindow::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }

    double RenderWindow::Update() {
        glfwPollEvents();
        static double lastTime = GetTime();
        double currentTime = GetTime();
        double delta = currentTime - lastTime;
        lastTime = currentTime;
        return delta;
    }

    bool RenderWindow::ShouldClose() {
        return glfwWindowShouldClose(m_WindowHandle);
    }

    void RenderWindow::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderWindow::SetTitle(const std::string& title){
        glfwSetWindowTitle(m_WindowHandle, title.c_str());
    }

    double RenderWindow::GetTime(){
        return glfwGetTime();
    }

    GLFWwindow *RenderWindow::GetWindowHandle() {
        return m_WindowHandle;
    }

    RenderWindow::~RenderWindow()
    {
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
    }

}