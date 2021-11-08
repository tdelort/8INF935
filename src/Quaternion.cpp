#include "Quaterion.h"


Quaternion::Quaternion()
    : value({1, 0, 0, 0})
{ }

Quaternion::Quaternion(float w, float x, float y, float z)
    : value({w, x, y, z})
{ 
    // TODO : Check quaternion is valid
}

void Quaterion::Normalize()
{
    float length = sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2] + value[3] * value[3]);
    value[0] /= length;
    value[1] /= length;
    value[2] /= length;
    value[3] /= length;
}

Quaternion Quaterion::operator*(const Quaternion& other)
{
    value[0] = w() * other.w() - x() * other.x() - y() * other.y() - z() * other.z();
    value[1] = w() * other.x() + x() * other.w() + y() * other.z() - z() * other.y();
    value[2] = w() * other.y() + y() * other.w() + z() * other.x() - x() * other.z();
    value[3] = w() * other.z() + z() * other.w() + x() * other.y() - y() * other.x();
}

void Quaterion::RotateByVector(const Vector3D& vector)
{
    Quaternion q(0, vector.x(), vector.y(), vector.z());
    *this *= q;
}

void Quaterion::UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{
    // TO UNDERSTAND
}

// x y z w getters
float Quaterion::x() const
{
    return value[1];
}

float Quaterion::y() const
{
    return value[2];
}

float Quaterion::z() const
{
    return value[3];
}

float Quaterion::w() const
{
    return value[0];
}
