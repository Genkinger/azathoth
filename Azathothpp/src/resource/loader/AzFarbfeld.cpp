#include "resource/loader/AzFarbfeld.hpp"

//TODO: check for the correct magic in the header;
namespace Az{
    namespace Farbfeld{
        farbfeld_t Load(const String& path){
            farbfeld_t farbfeld;
            std::ifstream infile(path.c_str(),std::ios::binary);
            infile.read(reinterpret_cast<char*>(&farbfeld.header),sizeof(farbfeld_header_t));
            farbfeld.data.reserve(farbfeld.header.width * farbfeld.header.height * sizeof(int16_t));
            infile.read(reinterpret_cast<char*>(farbfeld.data.data()),farbfeld.header.width * farbfeld.header.height * sizeof(int16_t));
            infile.close();
            return farbfeld;
        }

        void Save(const String& path, farbfeld_t farbfeld){
            std::ofstream outfile(path.c_str(),std::ios::binary);
            outfile.write(reinterpret_cast<char*>(&farbfeld.header),sizeof(farbfeld_header_t));
            outfile.write(reinterpret_cast<char*>(farbfeld.data.data()),farbfeld.data.size() * sizeof(int8_t));
            outfile.close();
        }
    }
}