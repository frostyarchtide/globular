#include "globular/math/vec4.hpp"

#include <sstream>
#include <stdexcept>

template <typename T>
vec4<T> vec4<T>::operator+(const vec4& other) const {
    return vec4<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

template <typename T>
vec4<T> vec4<T>::operator-(const vec4& other) const {
    return vec4<T>(x - other.x, y - other.y, z - other.z, w - other.w);
}

template <typename T>
vec4<T> vec4<T>::operator*(T value) const {
    return vec4<T>(x * value, y * value, z * value, w * value);
}

template <typename T>
vec4<T> vec4<T>::operator/(T value) const {
    return vec4<T>(x / value, y / value, z / value, w / value);
}

template <typename T>
vec4<T>& vec4<T>::operator+=(const vec4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

template <typename T>
vec4<T>& vec4<T>::operator-=(const vec4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

template <typename T>
vec4<T>& vec4<T>::operator*=(T value) {
    x *= value;
    y *= value;
    z *= value;
    w *= value;
    return *this;
}

template <typename T>
vec4<T>& vec4<T>::operator/=(T value) {
    x /= value;
    y /= value;
    z /= value;
    w /= value;
    return *this;
}

template <typename T>
vec4<T> vec4<T>::operator-() const {
    return vec4<T>(-x, -y, -z, -w);
}

template <typename T>
T& vec4<T>::operator[](size_t index) {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    if (index == 3) return w;
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
const T& vec4<T>::operator[](size_t index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    if (index == 3) return w;
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
bool vec4<T>::operator==(const vec4& other) {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

template <typename T>
vec4<T>::operator std::string() const {
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const vec4<T>& vector) {
    stream
        << "("
        << vector.x
        << ", "
        << vector.y
        << ", "
        << vector.z
        << ", "
        << vector.w
        << ")";
    return stream;
}

template struct vec4<float>;
template struct vec4<double>;
template struct vec4<int>;
template struct vec4<unsigned int>;
template std::ostream& operator<< <float>(std::ostream&, const vec4<float>&);
template std::ostream& operator<< <double>(std::ostream&, const vec4<double>&);
template std::ostream& operator<< <int>(std::ostream&, const vec4<int>&);
template std::ostream& operator<< <unsigned int>(std::ostream&, const vec4<unsigned int>&);
