#pragma once

#include "vec4.hpp"

template <typename T = float>
struct mat4 {
    static_assert(
        std::is_same_v<T, float>
        || std::is_same_v<T, double>
        || std::is_same_v<T, int>
        || std::is_same_v<T, unsigned int>,
        "mat4<T>: T must be float, double, int, or unsigned int"
    );

    vec4<T> columns[4];

    explicit mat4(vec4<T> column_0 = vec4<T>(), vec4<T> column_1 = vec4<T>(), vec4<T> column_2 = vec4<T>(), vec4<T> column_3 = vec4<T>()) {
        columns[0] = column_0;
        columns[1] = column_1;
        columns[2] = column_2;
        columns[3] = column_3;
    }

    static mat4<T> identity();
    mat4 transpose();
    mat4 inverse_affine(bool orthonormal = false);

    mat4 operator+(const mat4& other) const;
    mat4 operator-(const mat4& other) const;
    mat4 operator*(T value) const;
    vec4<T> operator*(const vec4<T>& vector) const;
    mat4 operator*(const mat4& other) const;
    vec4<T>& operator[](size_t index);
    const vec4<T>& operator[](size_t index) const;
    operator std::string() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const mat4<T>& matrix);

extern template struct mat4<float>;
extern template struct mat4<double>;
extern template struct mat4<int>;
extern template struct mat4<unsigned int>;
extern template std::ostream& operator<< <float>(std::ostream&, const mat4<float>&);
extern template std::ostream& operator<< <double>(std::ostream&, const mat4<double>&);
extern template std::ostream& operator<< <int>(std::ostream&, const mat4<int>&);
extern template std::ostream& operator<< <unsigned int>(std::ostream&, const mat4<unsigned int>&);
