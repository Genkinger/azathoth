#pragma once

extern Az::Application* Az::CreateApplication(int argc, char **argv);
extern void Az::DestroyApplication(Az::Application* app);

int main(int argc, char **argv){
    Az::Application *app = Az::CreateApplication(argc,argv);
    app->Run();
    Az::DestroyApplication(app);
    return 0;
}