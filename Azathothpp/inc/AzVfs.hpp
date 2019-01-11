#pragma once
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "AzFsUtils.hpp"

namespace Az{
    class Vfs{
        std::map<std::string, std::vector<std::string> > mMountPoints;

        public:
            void Mount(const std::string& fslocation, const std::string& mountpoint);
            void Unmount(const std::string& mountpoint);
            std::vector<std::string> ResolvePath(const std::string& path);
            std::vector<std::string> Find(const std::string& file);

    };
}