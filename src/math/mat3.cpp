#include "globular/math/mat3.hpp"

#include <iomanip>

template <typename T>
mat3<T> mat3<T>::identity() {
    return mat3<T>(
        vec3<T>(1, 0, 0),
        vec3<T>(0, 1, 0),
        vec3<T>(0, 0, 1)
    );
}

template <typename T>
mat3<T> mat3<T>::transpose() const {
    return mat3<T>(
        vec3<T>(columns[0].x, columns[0].y, columns[0].z),
        vec3<T>(columns[1].x, columns[1].y, columns[1].z),
        vec3<T>(columns[2].x, columns[2].y, columns[2].z)
    );
}

template <typename T>
T mat3<T>::determinant() const {
    const vec3<T>& a = columns[0];
    const vec3<T>& b = columns[1];
    const vec3<T>& c = columns[2];

    return
        a.x * (b.y * c.z - b.z * c.y) -
        a.y * (b.x * c.z - b.z * c.x) +
        a.z * (b.x * c.y - b.y * c.x);
}

template <typename T>
mat3<T> mat3<T>::cofactor() const {
    const vec3<T>& a = columns[0];
    const vec3<T>& b = columns[1];
    const vec3<T>& c = columns[2];

    return mat3(
        vec3<T>(
            b.y * c.z - b.z * c.y,
            a.z * c.y - a.y * c.z,
            a.y * b.z - a.z * b.y
        ),
        vec3<T>(
            b.z * c.x - b.x * c.z,
            a.x * c.z - a.z * c.x,
            a.z * b.x - a.x * b.z
        ),
        vec3<T>(
            b.x * c.y - b.y * c.x,
            a.y * c.x - a.x * c.y,
            a.x * b.y - a.y * b.x
        )
    );
}

template <typename T>
mat3<T> mat3<T>::adjoint() const {
    return cofactor().transpose();
}

template <typename T>
mat3<T> mat3<T>::inverse() const {
    T det = determinant();
    if (std::abs((double) det) < 1.0e-6)
        throw std::runtime_error("Cannot invert matrix with zero determinant");

    return adjoint() * (T(1) / det);
}

template <typename T>
mat3<T> mat3<T>::operator+(const mat3<T>& other) const {
    return mat3<T>(
        columns[0] + other[0],
        columns[1] + other[1],
        columns[2] + other[2]
    );
}

template <typename T>
mat3<T> mat3<T>::operator-(const mat3<T>& other) const {
    return mat3<T>(
        columns[0] - other[0],
        columns[1] - other[1],
        columns[2] - other[2]
    );
}

template <typename T>
mat3<T> mat3<T>::operator*(T value) const {
    return mat3<T>(
        columns[0] * value,
        columns[1] * value,
        columns[2] * value
    );
}

template <typename T>
vec3<T> mat3<T>::operator*(const vec3<T>& vector) const {
    return vec3<T>(columns[0] * vector.x + columns[1] * vector.y + columns[2] * vector.z);
}

template <typename T>
mat3<T> mat3<T>::operator*(const mat3<T>& other) const {
    return mat3<T>(*this * other[0], *this * other[1], *this * other[2]);
}

template <typename T>
vec3<T>& mat3<T>::operator[](size_t index) {
    return columns[index];
}

template <typename T>
const vec3<T>& mat3<T>::operator[](size_t index) const {
    return columns[index];
}

template <typename T>
mat3<T>::operator std::string() const {
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const mat3<T>& matrix) {
    size_t column_widths[3] = { 0 };
    for (size_t row = 0; row <= 2; row++) {
        for (size_t column = 0; column <= 2; column++) {
            std::ostringstream string_stream;
            string_stream << matrix.columns[column][row];
            size_t width = string_stream.str().length();
            if (width > column_widths[column]) column_widths[column] = width;
        }
    }
    for (size_t row = 0; row <= 2; row++) {
        stream << std::string("| ");
        for (size_t column = 0; column <= 2; column++) {
            stream << std::setw(column_widths[column]) << matrix.columns[column][row] << " ";
        }
        stream << std::string("|\n");
    }
    return stream;
}

template struct mat3<float>;
template struct mat3<double>;
template struct mat3<int>;
template struct mat3<unsigned int>;
template std::ostream& operator<< <float>(std::ostream&, const mat3<float>&);
template std::ostream& operator<< <double>(std::ostream&, const mat3<double>&);
template std::ostream& operator<< <int>(std::ostream&, const mat3<int>&);
template std::ostream& operator<< <unsigned int>(std::ostream&, const mat3<unsigned int>&);
