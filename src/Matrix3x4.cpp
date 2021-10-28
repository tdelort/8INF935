#include "Matrix3x4.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "Quaternion.h"

#include <initializer_list>

Matrix3x4::Matrix3x4()
    : Matrix<double,3,4>()
{ }

Matrix3x4::Matrix3x4(std::initializer_list<std::initializer_list<double>> row_list)
    : Matrix<double,3,4>(row_list)
{ }

Matrix3x4 Matrix3x4::operator*(const Matrix3x4& other) const
{
    return Matrix3x4();
}
Matrix3x4 Matrix3x4::operator*(const Vector3D& other) const
{
    return Matrix3x4();
}

Matrix3x4 Matrix3x4::Inverse()
{
    return Matrix3x4();
}

void Matrix3x4::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p)
{

}

Vector3D Matrix3x4::TransformPosition(const Vector3D& vector)
{
    return Vector3D();
}

Vector3D Matrix3x4::TransformDirection(const Vector3D& vector)
{
    return Vector3D();
}
