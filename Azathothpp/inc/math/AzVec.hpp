#pragma once
#include <math.h>
#include <cstdarg>

namespace Az{

    template<typename T,int dim>
    class Vec{
        
            int mDimension = dim;
            T mElements[dim];
        public:
            Vec(T val = 0){
                  for(int i = 0; i < mDimension ; i++){
                    mElements[i] = val;
                }
            }

            float length() const{
                return sqrtf(dot(*this));
            }

            Vec<T,dim> normalize() const{
                Vec<T,dim> result;
                float len = length();
                for(int i = 0; i < mDimension; i++){
                    result.mElements[i] = mElements[i]/len;
                }
                return result;
            }
            
            float dot(const Vec<T,dim>& other) const{
                float sum = 0;
                for(int i = 0; i < mDimension; i++){
                    sum += mElements[i] * other[i];
                }
                return sum;
            }
            
            int dimension() const{
                return mDimension;
            }

            Vec<T,dim> cross(const Vec<T,dim>& other) const{
                Vec<T,dim> result;
                if(mDimension == 3){
                    result[0] = mElements[1] * other[2] - other[1] * mElements[2];
                    result[1] = mElements[2] * other[0] - other[2] * mElements[0];
                    result[2] = mElements[0] * other[1] - other[0] * mElements[1];
                }else{
                    //TODO: Log this
                }
                return result;
            }

            Vec<T,dim> add(const Vec<T,dim>& other) const{
                Vec<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    result[i] = mElements[i] + other[i];
                }
                return result;
            }

            Vec<T,dim> add(T scalar) const{
                Vec<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    result[i] = mElements[i] + scalar;
                }
                return result;
            }

            Vec<T,dim> subtract(const Vec<T,dim>& other) const{
                Vec<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    result[i] = mElements[i] - other[i];
                }
                return result;
            }

            Vec<T,dim> subtract(T scalar) const{
                Vec<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    result[i] = mElements[i] - scalar;
                }
                return result;
            }

            Vec<T,dim> multiply(T scalar) const{
                Vec<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    result[i] = mElements[i] * scalar;
                }
                return result;
            }

            T& operator[] (int i){
                return mElements[i];
            }

            Vec<T,dim> operator+(const Vec<T,dim>& other) const{
                return add(other);
            }
            
            Vec<T,dim> operator+(T scalar) const{
                return add(scalar);
            }
            
            Vec<T,dim> operator-(const Vec<T,dim>& other) const{
                return subtract(other);
            }

            Vec<T,dim> operator-(T scalar ) const{
                return subtract(scalar);
            }

            float operator*(const Vec<T,dim>& other) const{
                return dot(other);
            }

            Vec<T,dim> operator*(T scalar) const{
                return multiply(scalar);
            }

            Vec<T,dim> operator/(T scalar) const{
                return multiply(1/scalar);
            }

            
    }; 

    template<typename T>
    using Vec2 = Vec<T,2>;
    using Vec2f = Vec<float,2>;
    template<typename T>
    using Vec3 = Vec<T,3>;
    using Vec3f = Vec<float,3>;
    template<typename T>
    using Vec4 = Vec<T,4>;
    using Vec4f = Vec<float,4>;
    
}
