#include "globular/math/vec3.hpp"

#include <sstream>
#include <stdexcept>

template <typename T>
vec3<T> vec3<T>::operator+(const vec3& other) const {
    return vec3<T>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
vec3<T> vec3<T>::operator-(const vec3& other) const {
    return vec3<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
vec3<T> vec3<T>::operator*(T value) const {
    return vec3<T>(x * value, y * value, z * value);
}

template <typename T>
vec3<T> vec3<T>::operator/(T value) const {
    return vec3<T>(x / value, y / value, z / value);
}

template <typename T>
vec3<T>& vec3<T>::operator+=(const vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template <typename T>
vec3<T>& vec3<T>::operator-=(const vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template <typename T>
vec3<T>& vec3<T>::operator*=(T value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

template <typename T>
vec3<T>& vec3<T>::operator/=(T value) {
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

template <typename T>
vec3<T> vec3<T>::operator-() const {
    return vec3<T>(-x, -y, -z);
}

template <typename T>
T& vec3<T>::operator[](size_t index) {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
const T& vec3<T>::operator[](size_t index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
bool vec3<T>::operator==(const vec3& other) {
    return x == other.x && y == other.y && z == other.z;
}

template <typename T>
vec3<T>::operator std::string() const {
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const vec3<T>& vector) {
    stream
        << "("
        << vector.x
        << ", "
        << vector.y
        << ", "
        << vector.z
        << ")";
    return stream;
}

template struct vec3<float>;
template struct vec3<double>;
template struct vec3<int>;
template struct vec3<unsigned int>;
template std::ostream& operator<< <float>(std::ostream&, const vec3<float>&);
template std::ostream& operator<< <double>(std::ostream&, const vec3<double>&);
template std::ostream& operator<< <int>(std::ostream&, const vec3<int>&);
template std::ostream& operator<< <unsigned int>(std::ostream&, const vec3<unsigned int>&);
