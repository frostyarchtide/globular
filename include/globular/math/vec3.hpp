#pragma once

#include <string>
#include <type_traits>

template <typename T = float>
struct vec3 {
    static_assert(
        std::is_same_v<T, float>
        || std::is_same_v<T, double>
        || std::is_same_v<T, int>
        || std::is_same_v<T, unsigned int>,
        "vec3<T>: T must be float, double, int, or unsigned int"
    );

    T x, y, z;

    explicit vec3(T x = T(), T y = T(), T z = T()) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& other) const;
    vec3 operator-(const vec3& other) const;
    vec3 operator*(T value) const;
    vec3 operator/(T value) const;
    vec3& operator+=(const vec3& other);
    vec3& operator-=(const vec3& other);
    vec3& operator*=(T value);
    vec3& operator/=(T value);
    vec3 operator-() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    bool operator==(const vec3& other);
    operator std::string() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const vec3<T>& vector);

extern template struct vec3<float>;
extern template struct vec3<double>;
extern template struct vec3<int>;
extern template struct vec3<unsigned int>;
extern template std::ostream& operator<< <float>(std::ostream&, const vec3<float>&);
extern template std::ostream& operator<< <double>(std::ostream&, const vec3<double>&);
extern template std::ostream& operator<< <int>(std::ostream&, const vec3<int>&);
extern template std::ostream& operator<< <unsigned int>(std::ostream&, const vec3<unsigned int>&);
