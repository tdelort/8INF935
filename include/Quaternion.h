#pragma once

#include "Vector3D.h"

class Quaternion
{
private:
    // w (x y z)
    float value[4];

public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);

    void Normalize();

    Quaternion operator*(const Quaternion& other);

    void RotateByVector(const Vector3D& vector);

    void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

    // x y z w getters
    float x() const;
    float y() const;
    float z() const;
    float w() const;

    // x y z w setters
    float& x();
    float& y();
    float& z();
    float& w();
};