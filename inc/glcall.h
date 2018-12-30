#pragma once
#include "common.h"
#include <signal.h>
#define DBG


extern GLenum GLCheckError();
extern bool GLLogCall(const char* function, const char* file, int line);


#ifdef DBG
    #define GLCall(x) GLCheckError();\
            x; \
            if (!GLLogCall(#x, __FILE__, __LINE__)) raise(SIGTRAP);
#else
    #define GLCall(x) x
#endif