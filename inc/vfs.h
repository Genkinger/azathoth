#pragma once
#include "common.h"


class VFS
{
    public:
        void mount(const char *filepath, const char *virtual_path);
        FILE *open(const char *virtualpath);
};