#pragma once

#include <string>
#include <type_traits>

template <typename T = float>
struct vec2 {
    static_assert(
        std::is_same_v<T, float>
        || std::is_same_v<T, double>
        || std::is_same_v<T, int>
        || std::is_same_v<T, unsigned int>,
        "vec2<T>: T must be float, double, int, or unsigned int"
    );

    T x, y;

    explicit vec2(T x = T(), T y = T()) : x(x), y(y) {}

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    vec2 operator*(T value) const;
    vec2 operator/(T value) const;
    vec2& operator+=(const vec2& other);
    vec2& operator-=(const vec2& other);
    vec2& operator*=(T value);
    vec2& operator/=(T value);
    vec2 operator-() const;
    bool operator==(const vec2& other);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    operator std::string() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const vec2<T>& vector);

extern template struct vec2<float>;
extern template struct vec2<double>;
extern template struct vec2<int>;
extern template struct vec2<unsigned int>;
extern template std::ostream& operator<< <float>(std::ostream&, const vec2<float>&);
extern template std::ostream& operator<< <double>(std::ostream&, const vec2<double>&);
extern template std::ostream& operator<< <int>(std::ostream&, const vec2<int>&);
extern template std::ostream& operator<< <unsigned int>(std::ostream&, const vec2<unsigned int>&);
