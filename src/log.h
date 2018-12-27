#include "GL/glew.h"
#include <stdio.h>
#include <signal.h>
#define DBG

namespace LOG {
    extern GLenum GLCheckError();
    extern bool GLLogCall(const char* function, const char* file, int line);
}

#ifdef DBG
    #define GLCall(x) LOG::GLCheckError();\
            x; \
            if (!LOG::GLLogCall(#x, __FILE__, __LINE__)) raise(SIGTRAP);
#else
    #define GLCall(x) x
#endif