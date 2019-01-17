#include "Azathoth.hpp"
#include <iostream>


class Sandbox : public Az::Application{
        Az::RenderWindow   *mRenderWindow;
    public:
        Sandbox(int argc, char **argv): Application(argc,argv){
            mRenderWindow = new Az::RenderWindow(800,600,"Sandbox");
        }

        ~Sandbox(){
            mLogger.Info("Shutting down ... Bye!");
            delete mRenderWindow;
        }

        void Run(){
            mLogger.Critical("Now starting the app...");
            glClearColor(1,0.3,0.6,1);

            while(!mRenderWindow->ShouldClose()){
                mRenderWindow->Update();
                mRenderWindow->Clear();
                mRenderWindow->SwapBuffers();
            }
        }
};

Az::Application* Az::CreateApplication(int argc, char **argv){
    return new Sandbox(argc,argv);
}

void Az::DestroyApplication(Az::Application *app){
    delete app;
}