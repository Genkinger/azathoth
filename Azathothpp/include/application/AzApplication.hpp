#pragma once
#include "log/AzLogger.hpp"

namespace Az{
    class Application{

        protected:
            int     mArgc;
            char    **mArgv;
            Logger  mLogger;
        public:
            Application(int argc, char** argv);
            virtual ~Application();

            virtual void Run();
    };

    Application*    CreateApplication(int argc, char** argv);
    void            DestroyApplication(Application* app);
}