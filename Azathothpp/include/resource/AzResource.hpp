#pragma once

namespace Az{

    template<typename T>
    class Resource{
        T *mResourcePointer;
        public:
            Resource(T* resource_pointer): mResourcePointer(resource_pointer){}
            T* Get(){ return mResourcePointer; }
            ~Resource(){}    
    };
}