#include "Matrix3x4.h"
#include "Matrix3x3.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "Quaternion.h"

#include <initializer_list>

Matrix3x4::Matrix3x4()
    : Base()
{ }

Matrix3x4::Matrix3x4(std::initializer_list<std::initializer_list<float>> row_list)
    : Base(row_list)
{ }

Matrix3x4 Matrix3x4::operator*(const Matrix3x4& other) const
{
    Matrix3x4 res;
    // top left 3x3 works like with a 3x3 matrix
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            float a = (*this)(i, 0) * other(0, j);
            float b = (*this)(i, 1) * other(1, j);
            float c = (*this)(i, 2) * other(2, j);
            res(i, j) = a + b + c;
        }
    }

    // right row
    for (int i = 0; i < 3; i++)
    {
        float a = (*this)(i, 0) * other(0, 3);
        float b = (*this)(i, 1) * other(1, 3);
        float c = (*this)(i, 2) * other(2, 3);
        float d = (*this)(i, 3);
        res(i, 3) = a + b + c + d;
    }
    return res;
}

Vector3D Matrix3x4::operator*(const Vector3D& other) const
{
    return Vector3D(
        m_data[0] * other.x() + m_data[1] * other.y() + m_data[2]  * other.z() + m_data[3],
        m_data[4] * other.x() + m_data[5] * other.y() + m_data[6]  * other.z() + m_data[7],
        m_data[8] * other.x() + m_data[9] * other.y() + m_data[10] * other.z() + m_data[11]
    );
}

Matrix3x4 Matrix3x4::Inverse()
{
    Matrix3x3 topLeft = {
        {m_data[0], m_data[1], m_data[2]},
        {m_data[4], m_data[5], m_data[6]},
        {m_data[8], m_data[9], m_data[10]}
    };

    Matrix3x3 invTopLeft = topLeft.Inverse();

    Vector3D invTranslation = invTopLeft * Vector3D(-m_data[3], -m_data[7], -m_data[11]);

    Matrix3x4 res;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res(i, j) = invTopLeft(i, j);

    res(0, 3) = invTranslation.x();
    res(1, 3) = invTranslation.y();
    res(2, 3) = invTranslation.z();

    return res;
}

void Matrix3x4::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p)
{
    Matrix3x3 rot;
    rot.SetOrientation(q);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m_data[i * m_m + j] = rot(i, j);

    m_data[3] = p.x();
    m_data[7] = p.y();
    m_data[11] = p.z();
}

Vector3D Matrix3x4::TransformPosition(const Vector3D& vector)
{
    // That simple ?
    return (*this) * vector;
}

Vector3D Matrix3x4::TransformDirection(const Vector3D& vector)
{
    Matrix3x3 tmp = {
        {m_data[0], m_data[1], m_data[2]},
        {m_data[4], m_data[5], m_data[6]},
        {m_data[8], m_data[9], m_data[10]}
    };

    return tmp * vector;
}

Matrix3x3 Matrix3x4::ToMatrix3x3() const
{
    Matrix3x3 res = {
        {m_data[0], m_data[1], m_data[2]},
        {m_data[4], m_data[5], m_data[6]},
        {m_data[8], m_data[9], m_data[10]}
    };
    return res;
}