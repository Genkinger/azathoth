#include "application/AzApplication.hpp"
#include <stdio.h>


namespace Az{
    Application::Application(int argc, char **argv) : mArgc(argc), mArgv(argv), mLogger("Application"){}
    Application::~Application(){}
    void Application::Run(){}
}