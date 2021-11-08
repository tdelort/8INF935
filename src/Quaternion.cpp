#include "Quaterion.h"


Quaternion::Quaternion();
Quaternion::Quaternion(float w, float x, float y, float z);

void Quaterion::Normalize();

Quaternion Quaterion::operator*(const Quaternion& other);

void Quaterion::RotateByVector(const Vector3D& vector);

void Quaterion::UpdateByAngularVelocity(const Vector3D& rotation, float duration);

// x y z w getters
float Quaterion::x() const;
float Quaterion::y() const;
float Quaterion::z() const;
float Quaterion::w() const;