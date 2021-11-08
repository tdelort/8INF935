#include "Matrix3x3.h"
#include "Matrix.h"
#include "Vector3D.h"

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

Vector3D Matrix3x3::operator*(const Vector3D& other) const
{
    Vector3D res;
    for (int i = 0; i < 3; i++)
    {
        float a = m_data[i * m_m + 0] * other.x();
        float b = m_data[i * m_m + 1] * other.y();
        float c = m_data[i * m_m + 2] * other.z();
        res.setX(a + b + c);
    }
    return res;
}

Matrix3x3 Matrix3x3::Inverse()
{
    Matrix3x3 res;
    float det = (*this)(0, 0) * ((*this)(1, 1) * (*this)(2, 2) - (*this)(2, 1) * (*this)(1, 2)) -
                (*this)(0, 1) * ((*this)(1, 0) * (*this)(2, 2) - (*this)(2, 0) * (*this)(1, 2)) +
                (*this)(0, 2) * ((*this)(1, 0) * (*this)(2, 1) - (*this)(2, 0) * (*this)(1, 1));
    if (det == 0)
    {
        std::cerr << "Matrix3x3::Inverse(): determinant is zero" << std::endl;
        return res;
    }
    det = 1.0f / det;
    res(0, 0) = ((*this)(1, 1) * (*this)(2, 2) - (*this)(2, 1) * (*this)(1, 2)) * det;
    res(0, 1) = ((*this)(0, 2) * (*this)(2, 1) - (*this)(0, 1) * (*this)(2, 2)) * det;
    res(0, 2) = ((*this)(0, 1) * (*this)(1, 2) - (*this)(0, 2) * (*this)(1, 1)) * det;
    res(1, 0) = ((*this)(1, 2) * (*this)(2, 0) - (*this)(1, 0) * (*this)(2, 2)) * det;
    res(1, 1) = ((*this)(0, 0) * (*this)(2, 2) - (*this)(0, 2) * (*this)(2, 0)) * det;
    res(1, 2) = ((*this)(1, 0) * (*this)(0, 2) - (*this)(0, 0) * (*this)(1, 2)) * det;
    res(2, 0) = ((*this)(1, 0) * (*this)(2, 1) - (*this)(2, 0) * (*this)(1, 1)) * det;
    res(2, 1) = ((*this)(2, 0) * (*this)(0, 1) - (*this)(0, 0) * (*this)(2, 1)) * det;
    res(2, 2) = ((*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1)) * det;
    return res;
}

Matrix3x3 Matrix3x3::Transpose()
{
    Matrix3x3 res;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res(i, j) = (*this)(j, i);

    return res;
}

void Matrix3x3::SetOrientation(const Quaternion& q)
{
    float w = q.w();
    float x = q.x();
    float y = q.y();
    float z = q.z();

    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;

    (*this)(0,0) = 1.0f - (2.0f * y2 + 2.0f * z2);
    (*this)(1,0) = 2.0f * (x * y - z * w);
    (*this)(2,0) = 2.0f * (x * z + w * y);

    (*this)(0,1) = 2.0f * (x * y + w * z);
    (*this)(1,1) = 1.0f - (2.0f * x2 + 2.0f * z2);
    (*this)(2,1) = 2.0f * (y * z - w * x);

    (*this)(0,2) = 2.0f * (x * z - w * y);
    (*this)(1,2) = 2.0f * (y * z + w * x);
    (*this)(2,2) = 1.0f - (2.0f * x2 + 2.0f * y2);
}
