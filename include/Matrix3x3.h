#pragma once

#include "Matrix.h"
#include <initializer_list>

class Quaternion;
class Vector3D;

class Matrix3x3 : public Matrix<double,3,3>
{
public:
    Matrix3x3();
    Matrix3x3(std::initializer_list<std::initializer_list<double>>);

    Matrix3x3 operator*(const Matrix3x3& other) const;
    Matrix3x3 operator*(const Vector3D& other) const;

    Matrix3x3 Inverse();
    Matrix3x3 Transpose();

    void SetOrientation(const Quaternion& q);
};