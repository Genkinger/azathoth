#include <stdint.h>
#include "string/AzString.hpp"
#include <fstream>
#include <vector>


namespace Az{
    namespace Farbfeld{
        struct farbfeld_header_t
        {
            int8_t      magic[8];
            uint32_t    width;
            uint32_t    height;
        };

        struct farbfeld_t
        {
            farbfeld_header_t   header;
            std::vector<int8_t> data;

        };

        farbfeld_t Load(const String& path);
        void Save(const String& path, farbfeld_t farbfeld);
        
    }
}

