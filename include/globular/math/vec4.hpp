#pragma once

#include <string>
#include <type_traits>

template <typename T = float>
struct vec4 {
    static_assert(
        std::is_same_v<T, float>
        || std::is_same_v<T, double>
        || std::is_same_v<T, int>
        || std::is_same_v<T, unsigned int>,
        "vec4<T>: T must be float, double, int, or unsigned int"
    );

    T x, y, z, w;

    explicit vec4(T x = T(), T y = T(), T z = T(), T w = T()) : x(x), y(y), z(z), w(w) {}

    vec4 operator+(const vec4& other) const;
    vec4 operator-(const vec4& other) const;
    vec4 operator*(T value) const;
    vec4 operator/(T value) const;
    vec4& operator+=(const vec4& other);
    vec4& operator-=(const vec4& other);
    vec4& operator*=(T value);
    vec4& operator/=(T value);
    vec4 operator-() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    bool operator==(const vec4& other);
    operator std::string() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const vec4<T>& vector);

extern template struct vec4<float>;
extern template struct vec4<double>;
extern template struct vec4<int>;
extern template struct vec4<unsigned int>;
extern template std::ostream& operator<< <float>(std::ostream&, const vec4<float>&);
extern template std::ostream& operator<< <double>(std::ostream&, const vec4<double>&);
extern template std::ostream& operator<< <int>(std::ostream&, const vec4<int>&);
extern template std::ostream& operator<< <unsigned int>(std::ostream&, const vec4<unsigned int>&);
