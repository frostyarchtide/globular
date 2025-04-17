#include "globular/math/vec2.hpp"

#include <sstream>
#include <stdexcept>

template <typename T>
vec2<T> vec2<T>::operator+(const vec2& other) const {
    return vec2<T>(x + other.x, y + other.y);
}

template <typename T>
vec2<T> vec2<T>::operator-(const vec2& other) const {
    return vec2<T>(x - other.x, y - other.y);
}

template <typename T>
vec2<T> vec2<T>::operator*(T value) const {
    return vec2<T>(x * value, y * value);
}

template <typename T>
vec2<T> vec2<T>::operator/(T value) const {
    return vec2<T>(x / value, y / value);
}

template <typename T>
vec2<T>& vec2<T>::operator+=(const vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
vec2<T>& vec2<T>::operator-=(const vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

template <typename T>
vec2<T>& vec2<T>::operator*=(T value) {
    x *= value;
    y *= value;
    return *this;
}

template <typename T>
vec2<T>& vec2<T>::operator/=(T value) {
    x /= value;
    y /= value;
    return *this;
}

template <typename T>
vec2<T> vec2<T>::operator-() const {
    return vec2<T>(-x, -y);
}

template <typename T>
bool vec2<T>::operator==(const vec2& other) {
    return x == other.x && y == other.y;
}

template <typename T>
T& vec2<T>::operator[](size_t index) {
    if (index == 0) return x;
    if (index == 1) return y;
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
const T& vec2<T>::operator[](size_t index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    throw std::out_of_range("Index out of bounds");
}

template <typename T>
vec2<T>::operator std::string() const {
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const vec2<T>& vector) {
    stream
        << "("
        << vector.x
        << ", "
        << vector.y
        << ")";
    return stream;
}

template struct vec2<float>;
template struct vec2<double>;
template struct vec2<int>;
template struct vec2<unsigned int>;
template std::ostream& operator<< <float>(std::ostream&, const vec2<float>&);
template std::ostream& operator<< <double>(std::ostream&, const vec2<double>&);
template std::ostream& operator<< <int>(std::ostream&, const vec2<int>&);
template std::ostream& operator<< <unsigned int>(std::ostream&, const vec2<unsigned int>&);
