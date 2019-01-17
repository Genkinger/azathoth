#include "system/AzFilesystem.hpp"


namespace Az{
    bool Fs::Exists(const std::string& filepath){
        struct stat buffer;
        return (stat(filepath.c_str(),&buffer) == 0);
    }
}