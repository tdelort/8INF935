#pragma once

#include "Matrix.h"
#include <initializer_list>

class Quaternion;
class Vector3D;

class Matrix3x3 : public Matrix<float,3,3>
{
    using Base = Matrix<float,3,3>;
public:
    Matrix3x3();
    Matrix3x3(std::initializer_list<std::initializer_list<float>>);

    Matrix3x3 operator*(const Matrix3x3& other) const;
    Vector3D operator*(const Vector3D& other) const;

    Matrix3x3 Inverse();
    Matrix3x3 Transpose();

    void SetOrientation(const Quaternion& q);

};