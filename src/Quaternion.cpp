#include "Quaternion.h"

#include "Vector3D.h"

#include <iostream>

Quaternion::Quaternion()
    : value{1, 0, 0, 0}
{ }

Quaternion::Quaternion(float w, float x, float y, float z)
    : value{w, x, y, z}
{ 

}

void Quaternion::Normalize()
{
    float length = sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2] + value[3] * value[3]);
    if(length == 0)
    {
        std::cerr << "Quaternion::Normalize() : Quaternion is zero" << std::endl;
        exit(1);
    }
    float invlength = 1.0f / length;
    value[0] *= invlength;
    value[1] *= invlength;
    value[2] *= invlength;
    value[3] *= invlength;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
    Quaternion result;
    result.w() = w() * other.w() - x() * other.x() - y() * other.y() - z() * other.z();
    result.x() = w() * other.x() + x() * other.w() + y() * other.z() - z() * other.y();
    result.y() = w() * other.y() + y() * other.w() + z() * other.x() - x() * other.z();
    result.z() = w() * other.z() + z() * other.w() + x() * other.y() - y() * other.x();
    return result;
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{
    Quaternion omega(
        0.0f,
        rotation.x(),
        rotation.y(),
        rotation.z()
    );
    //std::cout << "tmp : " << tmp.w() << " " << tmp.x() << " " << tmp.y() << " " << tmp.z() << std::endl;
    Quaternion tmp = omega * *this;
    w() = w() + 0.5f * duration * tmp.w();
    x() = x() + 0.5f * duration * tmp.x();
    y() = y() + 0.5f * duration * tmp.y();
    z() = z() + 0.5f * duration * tmp.z();
}

Vector3D Quaternion::Euler() const
{   
    Vector3D result;
    result.setX(atan2(2.0f * (w() * x() + y() * z()), 1.0f - 2.0f * (x() * x() + y() * y())));
    result.setY(asin(2.0f * (w() * y() - z() * x())));
    result.setZ(atan2(2.0f * (w() * z() + x() * y()), 1.0f - 2.0f * (y() * y() + z() * z())));
    return result;
}

Quaternion Quaternion::AngleTo(const Vector3D& from, const Vector3D& to)
{
    Vector3D a = from.normalize();
    Vector3D b = to.normalize();
    
    float d = a.dot(b);
    if(d > 0.99)
        return Quaternion(1, 0, 0, 0);
    if(d < -0.99)
        return Quaternion(0, 0, 1, 0);

    Vector3D c = Vector3D::cross(a, b);
    Quaternion result;
    result.x() = c.x();
    result.y() = c.y();
    result.z() = c.z();
    result.w() = 1 + d;
    result.Normalize();
    return result;
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
