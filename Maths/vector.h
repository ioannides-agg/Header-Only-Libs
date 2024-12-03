#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <vector>

namespace {

template <size_t DIM , typename T> 
class vec {
    protected:
      T components[DIM];
      int len = DIM;
      
    public:

      T operator[](int i) const {return components[i]; } //non-mutable
      T& operator[](int i) {return components[i]; } //mutable

      vec& operator-() {return *this *= -1; }

      vec& operator+=(const vec& v) {
        for (int i = 0; i < len; i++) {
            components[i] += v[i];
        }

        return *this;
      }

      vec& operator-=(const vec& v) {
        return *this+= -v;
      }

      vec& operator*=(auto scalar) {
        for (int i = 0; i < len; i++)
        {
            components[i] *= scalar;
        }

        return *this;
      }

      vec& operator/=(auto scalar) {
        return *this *= 1/scalar;
      }

      auto length_squared() {
        auto length = 0;
        for (int i = 0; i < len; i++)
        {
            length += components[i]*components[i];
        }

        return length;
      }

      auto length() {return std::sqrt(length_squared()); }
};

template <typename T>
class vec2 : public vec<2, T> {
    public:
      vec2(T x, T y) { 
        vec<2,T>::components[0] = x; 
        vec<2,T>::components[1] = y;}
};

template <typename T>
class vec3 : public vec<3,T> {
    public:
      vec3(T x, T y, T z) { 
        vec<3,T>::components[0] = x; 
        vec<3,T>::components[1] = y;
        vec<3,T>::components[2] = z;}
};

template <typename T>
class vec4 : public vec<4, T> {
    public:
      vec4(T x, T y, T z, T w) { 
        vec<4,T>::components[0] = x; 
        vec<4,T>::components[1] = y;
        vec<4,T>::components[2] = z;
        vec<4,T>::components[3] = w; }
};

//standard operator implementations for our vector class

template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, const vec<DIM, T>& v) {
    for(size_t i=0; i<DIM; i++) {
        out << v[i] << " " ;
    }
    return out ;
}

//for the sake of simplicity we pass the vector v by copy, 
//so we can just return the altered copy without changing the initial value of v

template <size_t DIM, typename T> vec<DIM, T> operator+(const vec<DIM, T> v, const vec<DIM, T>& u) {
    return (v += u);
}

template <size_t DIM, typename T> vec<DIM, T> operator-(const vec<DIM, T> v, const vec<DIM, T>& u) {
    return (v -= u);
}

template <size_t DIM, typename T> vec<DIM, T> operator*(const vec<DIM, T> v, const vec<DIM, T>& u) {
    for(size_t i=0; i<DIM; i++) {
        v[i] *= u[i];
    } 

    return v;
}

template <size_t DIM, typename T> vec<DIM, T> operator*(const vec<DIM, T> v, double& t) {
    return v *= t;
}

template <size_t DIM, typename T> vec<DIM, T> operator*(double& t, const vec<DIM, T> v) {
    return v *= t;
}

}

namespace rtc {

//for the sake of simplicity i ve implemented type definitions 
//of each vector length and type we are gonna need
//as well the point definition for extra clarity.

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;
using point2f = vec2f;
using point2i = vec2i;

typedef vec3<float> vec3f;
typedef vec3<int> vec3i;
using point3f = vec3f;
using point3i = vec3i;

typedef vec4<float> vec4f;
typedef vec4<int> vec4i;

template <size_t DIM, typename T> double dot(const vec<DIM, T>& v, const vec<DIM, T>& u) {
    T total = 0;
    for(size_t i=0; i<DIM; i++) {
        total += v[i] * u[i];
    } 

    return total;
}

//implementation of cross product is only for 3d vectors since 
//the space we are programming in is a euclidean one
template <typename T> vec3<T> cross(const vec3<T>& v, const vec3<T>& u) {
    return vec3<T>(v.vals[1] * u.vals[2] - v.vals[2] * u.vals[1],
                   v.vals[2] * u.vals[0] - v.vals[0] * u.vals[2],
                   v.vals[0] * u.vals[1] - v.vals[1] * u.vals[0]);
}
}

#endif /* VECTOR_H */