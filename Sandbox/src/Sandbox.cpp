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
            auto vfs = Az::Vfs();
            vfs.Mount("/home/genkinger","/");
            vfs.Mount("/home/genkinger/downloads","/test");
            vfs.Mount("/home","/");
            auto full = vfs.ResolvePath("/.bashrc");
            auto full2 = vfs.ResolvePath("/test/.bashrc");
            mLogger.Info("Found /.bashrc -> "+full[0]);
            mLogger.Info("Found /test/.bashrc -> "+full2[0]);
            
            
        }
};

Az::Application* Az::CreateApplication(int argc, char **argv){
    return new Sandbox(argc,argv);
}

void Az::DestroyApplication(Az::Application *app){
    delete app;
}