#include "log.h"

namespace LOG{
    GLenum GLCheckError()
    {
            return glGetError();
    }

    bool GLLogCall(const char* function, const char* file, int line)
    {
        GLenum error = GLCheckError();
        if (error != GL_NO_ERROR)
        {
            printf("[OpenGL Error] (%d): %s %s:%d\n", error, function, file, line);
            return false;
        }
        return true;
    }
}
