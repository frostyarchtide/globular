#pragma once

#include "vec3.hpp"
#include "mat4.hpp"

#include <type_traits>

template <typename T = float>
struct mat3 {
    static_assert(
        std::is_same_v<T, float>
        || std::is_same_v<T, double>
        || std::is_same_v<T, int>
        || std::is_same_v<T, unsigned int>,
        "mat3<T>: T must be float, double, int, or unsigned int"
    );

    vec3<T> columns[3];

    explicit mat3(vec3<T> column_0 = vec3<T>(), vec3<T> column_1 = vec3<T>(), vec3<T> column_2 = vec3<T>()) {
        columns[0] = column_0;
        columns[1] = column_1;
        columns[2] = column_2;
    }

    explicit mat3(const mat4<T>& matrix = mat4<T>()) {
        columns[0] = vec3<T>(matrix[0].x, matrix[0].y, matrix[0].z);
        columns[1] = vec3<T>(matrix[1].x, matrix[1].y, matrix[1].z);
        columns[2] = vec3<T>(matrix[2].x, matrix[2].y, matrix[2].z);
    }

    static mat3 identity();
    mat3 transpose() const;
    T determinant() const;
    mat3 cofactor() const;
    mat3 adjoint() const;
    mat3 inverse() const;

    mat3 operator+(const mat3<T>& other) const;
    mat3 operator-(const mat3<T>& other) const;
    mat3 operator*(T value) const;
    vec3<T> operator*(const vec3<T>& vector) const;
    mat3 operator*(const mat3<T>& other) const;
    vec3<T>& operator[](size_t index);
    const vec3<T>& operator[](size_t index) const;
    operator std::string() const;
};

template <typename T>
std::ostream& operator<<(std::ostream& stream, const mat3<T>& matrix);

extern template struct mat3<float>;
extern template struct mat3<double>;
extern template struct mat3<int>;
extern template struct mat3<unsigned int>;
extern template std::ostream& operator<< <float>(std::ostream&, const mat3<float>&);
extern template std::ostream& operator<< <double>(std::ostream&, const mat3<double>&);
extern template std::ostream& operator<< <int>(std::ostream&, const mat3<int>&);
extern template std::ostream& operator<< <unsigned int>(std::ostream&, const mat3<unsigned int>&);
