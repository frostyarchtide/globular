#include "globular/math/mat4.hpp"
#include "globular/math/mat3.hpp"

#include <iomanip>

template <typename T>
mat4<T> mat4<T>::identity() {
    return mat4<T>(
        vec4<T>(1, 0, 0, 0),
        vec4<T>(0, 1, 0, 0),
        vec4<T>(0, 0, 1, 0),
        vec4<T>(0, 0, 0, 1)
    );
}

template <typename T>
mat4<T> mat4<T>::transpose() {
    return mat4<T>(
        vec4<T>(columns[0].x, columns[0].y, columns[0].z, columns[0].w),
        vec4<T>(columns[1].x, columns[1].y, columns[1].z, columns[1].w),
        vec4<T>(columns[2].x, columns[2].y, columns[2].z, columns[2].w),
        vec4<T>(columns[3].x, columns[3].y, columns[3].z, columns[3].w)
    );
}

template <typename T>
mat4<T> mat4<T>::inverse_affine(bool orthonormal) {
    mat3<T> basis = mat3(*this);
    vec3<T> translation = vec3(columns[3].x, columns[3].y, columns[3].z);

    basis = (orthonormal) ? basis.transpose() : basis.inverse();
    translation = basis * (-translation);

    return mat4<T>(
        vec4<T>(basis[0].x, basis[0].y, basis[0].z, 0),
        vec4<T>(basis[1].x, basis[1].y, basis[1].z, 0),
        vec4<T>(basis[2].x, basis[2].y, basis[2].z, 0),
        vec4<T>(translation.x, translation.y, translation.z, 1)
    );
}

template <typename T>
mat4<T> mat4<T>::operator+(const mat4<T>& other) const {
    return mat4<T>(
        columns[0] + other[0],
        columns[1] + other[1],
        columns[2] + other[2],
        columns[3] + other[3]
    );
}

template <typename T>
mat4<T> mat4<T>::operator-(const mat4<T>& other) const {
    return mat4<T>(
        columns[0] - other[0],
        columns[1] - other[1],
        columns[2] - other[2],
        columns[3] - other[3]
    );
}

template <typename T>
mat4<T> mat4<T>::operator*(T value) const {
    return mat4<T>(
        columns[0] * value,
        columns[1] * value,
        columns[2] * value,
        columns[3] * value
    );
}

template <typename T>
vec4<T> mat4<T>::operator*(const vec4<T>& vector) const {
    return vec4<T>(
        columns[0] * vector.x +
        columns[1] * vector.y +
        columns[2] * vector.z +
        columns[3] * vector.w
    );
}

template <typename T>
mat4<T> mat4<T>::operator*(const mat4<T>& other) const {
    return mat4<T>(
        *this * other[0],
        *this * other[1],
        *this * other[2],
        *this * other[3]
    );
}

template <typename T>
vec4<T>& mat4<T>::operator[](size_t index) {
    return columns[index];
}

template <typename T>
const vec4<T>& mat4<T>::operator[](size_t index) const {
    return columns[index];
}

template <typename T>
mat4<T>::operator std::string() const {
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const mat4<T>& matrix) {
    size_t column_widths[4] = { 0 };
    for (size_t row = 0; row <= 3; row++) {
        for (size_t column = 0; column <= 3; column++) {
            std::ostringstream string_stream;
            string_stream << matrix.columns[column][row];
            size_t width = string_stream.str().length();
            if (width > column_widths[column]) column_widths[column] = width;
        }
    }
    for (size_t row = 0; row <= 3; row++) {
        stream << std::string("| ");
        for (size_t column = 0; column <= 3; column++) {
            stream << std::setw(column_widths[column]) << matrix.columns[column][row] << " ";
        }
        stream << std::string("|\n");
    }
    return stream;
}

template struct mat4<float>;
template struct mat4<double>;
template struct mat4<int>;
template struct mat4<unsigned int>;
template std::ostream& operator<< <float>(std::ostream&, const mat4<float>&);
template std::ostream& operator<< <double>(std::ostream&, const mat4<double>&);
template std::ostream& operator<< <int>(std::ostream&, const mat4<int>&);
template std::ostream& operator<< <unsigned int>(std::ostream&, const mat4<unsigned int>&);
