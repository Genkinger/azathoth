#pragma once

#include "AzVec.hpp"

namespace Az{

    template<typename T, int dim>
    class Mat{
            int mDimension = dim;
            T mElements[dim][dim];
        public:

            Mat(T value = 1){
                for(int i = 0; i < mDimension; i++){
                    for(int j = 0; j < mDimension; j++){
                        if(i == j){
                            mElements[i][j] = value;
                        }else{
                            mElements[i][j] = 0;
                        }
                    }
                }
            }

            Mat<T,dim> multiply(const Mat<T,dim>& other) const {
                Mat<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    for(int j = 0; j < mDimension; j++){
                        T sum = 0;
                        for(int k = 0; k < mDimension; k++){
                            sum += mElements[i][k] * other[k][j];   
                        }
                        result[i][j] = sum;
                    }
                }
                return result;
            }

            Vec<T,dim> multiply(const Vec<T,dim>& other) const{
                Vec<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                        T sum = 0;
                        for(int k = 0; k < mDimension; k++){
                            sum += mElements[i][k] * other[k];  
                        }
                        result[i] = sum;
                }
                return result;
            }

            Mat<T,dim> transpose() const{
                Mat<T,dim> result;
                for(int i = 0; i < mDimension; i++){
                    for(int j = 0; j < mDimension; j++){
                        result[i][j] = mElements[j][i];
                    }
                }
                return result;
            }

            Mat<T,dim> inverse() const{
                Mat<T,dim> result;
                //TODO: implement this behemoth...
                return result;
            }

            T& operator[](int i) {
                return mElements[i];
            }

            Mat<T,dim> operator*(const Mat<T,dim>& other) const{
                return multiply(other);
            }

            Vec<T,dim> operator*(const Vec<T,dim>& other) const{
                return multiply(other);
            }
    };

    template<typename T>
    using Mat4 = Mat<T,4>;
    using Mat4f = Mat<float,4>;
    template<typename T>
    using Mat3 = Mat<T,3>;
    using Mat3f = Mat<float,3>;
    

}