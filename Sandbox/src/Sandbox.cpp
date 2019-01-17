#include "Azathoth.hpp"
#include <iostream>


class Sandbox : public Az::Application{
        Az::LoggerFileSink *mFileSink;
        Az::RenderWindow   *mRenderWindow;
    public:
        Sandbox(int argc, char **argv): Application(argc,argv), mFileSink(){
            mFileSink = new Az::LoggerFileSink("FileSink");
            mLogger.AttachSink(mFileSink);

            mRenderWindow = new Az::RenderWindow(800,600,"Sandbox");
        }

        ~Sandbox(){
            mLogger.Info("Shutting down ... Bye!");
            delete mFileSink;
            delete mRenderWindow;
        }

        void Run(){
            mLogger.Critical("Now starting the app...");
            glClearColor(1,0,0,1);

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