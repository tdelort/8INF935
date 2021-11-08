#include "Matrix3x3.h"
#include "Matrix.h"

#include <initializer_list>

Matrix3x3::Matrix3x3()
    : Base()
{ }

Matrix3x3::Matrix3x3(std::initializer_list<std::initializer_list<float>> row_list)
    : Base(row_list)
{ }

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const
{
    Matrix3x3 res;
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            float a = m_data[i * m_m + 0] * other(0, j);
            float b = m_data[i * m_m + 1] * other(1, j);
            float c = m_data[i * m_m + 2] * other(2, j);
            res(i, j) = a + b + c;
        }
    }
    return res;
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
