#include "Quaternion.h"

#include <iostream>

Quaternion::Quaternion()
    : value{1, 0, 0, 0}
{ }

Quaternion::Quaternion(float w, float x, float y, float z)
    : value{w, x, y, z}
{ 
    // TODO : Check quaternion is valid
    Normalize();
}

void Quaternion::Normalize()
{
    float length = sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2] + value[3] * value[3]);
    if(length == 0)
    {
        std::cerr << "Quaternion::Normalize() : Quaternion is zero" << std::endl;
        exit(1);
    }
    length = 1.0f / length;
    value[0] *= length;
    value[1] *= length;
    value[2] *= length;
    value[3] *= length;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
    Quaternion result;
    result.w() = w() * other.w() - x() * other.x() - y() * other.y() - z() * other.z();
    result.x() = w() * other.x() + x() * other.w() + y() * other.z() - z() * other.y();
    result.y() = w() * other.y() + y() * other.w() + z() * other.x() - x() * other.z();
    result.z() = w() * other.z() + z() * other.w() + x() * other.y() - y() * other.x();
    result.Normalize();
    return result;
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
    Quaternion q(0, vector.x(), vector.y(), vector.z());
    *this = (*this) * q;
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{
    Quaternion q(0, rotation.x() * duration, rotation.y() * duration, rotation.z() * duration);
    *this = (*this) * q;
}

// x y z w getters
float Quaternion::x() const
{ return value[1];}

float Quaternion::y() const
{ return value[2];}

float Quaternion::z() const
{ return value[3];}

float Quaternion::w() const
{ return value[0];}

//x y z w setters
float& Quaternion::x()
{ return value[1];}

float& Quaternion::y()
{ return value[2];}

float& Quaternion::z()
{ return value[3];}

float& Quaternion::w()
{ return value[0];}
