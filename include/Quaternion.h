#pragma once

class Quaternion
{
private:
    float value[4];

public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);

    void Normalize();

    Quaternion operator*(const Quaternion& other);

    void RotateByVector(const Vector3D& vector);

    void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

    // x y z w getters
    float x() const;
    float y() const;
    float z() const;
    float w() const;
};