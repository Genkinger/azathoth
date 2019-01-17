#pragma once
#include <string>
#include <sys/stat.h>

namespace Az{

    struct Fs{
        static bool Exists(const std::string& filepath);
    };

}