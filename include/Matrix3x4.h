#pragma once

#include "Matrix.h"
#include "Matrix3x3.h"
#include <initializer_list>

class Quaternion;
class Vector3D;

class Matrix3x4 : public Matrix<float,3,4>
{
    using Base = Matrix<float,3,4>;
public:
    Matrix3x4();
    Matrix3x4(std::initializer_list<std::initializer_list<float>>);

    Matrix3x4 operator*(const Matrix3x4& other) const;
    Vector3D operator*(const Vector3D& other) const;

    Matrix3x4 Inverse();

    void SetOrientationAndPosition(const Quaternion& q, const Vector3D& p);

    Vector3D TransformPosition(const Vector3D& vector);
    Vector3D TransformDirection(const Vector3D& vector);

    Matrix3x3 ToMatrix3x3() const;

    Vector3D GetPosition() const;

    static Matrix3x4 Identity() { 
        return Matrix3x4({
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0}
        }); 
    }
};