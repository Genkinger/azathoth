#include "Azathoth.hpp"
#include <iostream>


class Sandbox : public Az::Application{
        Az::LoggerFileSink *mFileSink;
    public:
        Sandbox(int argc, char **argv): Application(argc,argv), mFileSink(){
            mFileSink = new Az::LoggerFileSink("FileSink");
            mLogger.AttachSink(mFileSink);
        }
        ~Sandbox(){
            mLogger.Info("Shutting down ... Bye!");
            delete mFileSink;
        }
        void Run(){
           mLogger.Critical("Now starting the app...");
        }
};

Az::Application* Az::CreateApplication(int argc, char **argv){
    return new Sandbox(argc,argv);
}

void Az::DestroyApplication(Az::Application *app){
    delete app;
}