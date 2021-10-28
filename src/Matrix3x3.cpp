#include "Matrix3x3.h"
#include "Matrix.h"

#include <initializer_list>

Matrix3x3::Matrix3x3()
    : Matrix<double,3,3>()
{ }

Matrix3x3::Matrix3x3(std::initializer_list<std::initializer_list<float>> row_list)
    : Matrix<double,3,3>(row_list)
{ }

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const
{
    return Matrix3x3();
}

Matrix3x3 Matrix3x3::operator*(const Vector3D& other) const
{
    return Matrix3x3();
}

Matrix3x3 Matrix3x3::Inverse()
{
    return Matrix3x3();
}

Matrix3x3 Matrix3x3::Transpose()
{
    return Matrix3x3();
}

void Matrix3x3::SetOrientation(const Quaternion& q)
{

}
