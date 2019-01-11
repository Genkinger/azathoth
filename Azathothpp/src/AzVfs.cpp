#include "AzVfs.hpp"



namespace Az{
    void Vfs::Mount(const std::string& fslocation, const std::string& mountpoint)
    {
        mMountPoints[mountpoint].emplace_back(fslocation);
    }
    void Vfs::Unmount(const std::string& mountpoint)
    {
       mMountPoints.erase(mountpoint);
    }
    //NOTE: THIS IS WRONG!!!!
    std::vector<std::string> Vfs::ResolvePath(const std::string& path){
        std::vector<std::string> result;
        for(auto mountpoint : mMountPoints){
            if(path.rfind(mountpoint.first,0) == 0){
                for(auto p : mountpoint.second){
                    std::string fullpath = path;
                    fullpath.replace(0,mountpoint.first.length(),p);
                    result.emplace_back(fullpath);
                }
            }
        }
        return result;
    }
    std::vector<std::string> Vfs::Find(const std::string& file){
        std::vector<std::string> result;
        for(auto kv : mMountPoints){
            auto it = std::find_if(std::begin(kv.second),std::end(kv.second),[&](const std::string& fspath){
                std::string fullpath = fspath + "/" + file;
                return Fs::Exists(fullpath);
            });
            if(it != std::end(kv.second)){
                result.emplace_back(*it + '/' + file);
            }
        }
        return result;
    }
    
}