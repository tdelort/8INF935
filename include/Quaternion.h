#pragma once

#include "Vector3D.h"

class Quaternion
{
private:
    // w (x y z)
    float value[4];

public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);

    void Normalize();

    Quaternion operator*(const Quaternion& other);

    void RotateByVector(const Vector3D& vector);

    void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

    Vector3D Euler() const;

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