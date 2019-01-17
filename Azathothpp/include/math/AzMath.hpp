#pragma once

#include "AzMat.hpp"
#include "AzVec.hpp"

namespace Az{

    template<typename T>
    T Clamp(T value, T min, T max){
        if(value < min)
            return min;
        if(value > max)
            return max;
        return value;
    }

    template<typename T>
    T Map(T value, T in_min, T in_max, T out_min, T out_max){
        return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    template<typename T>
    T Lerp(T value, T goal, float percent){
         return (1 - percent) * value + percent * goal;
    }

}