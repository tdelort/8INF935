#pragma once

#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix3x4.h"

class RigidBody
{
    private:
    float m_invMass;
    float m_angularDamping;
    Vector3D m_velocity;
    Vector3D m_position;

    Quaternion m_orientation;

    Vector3D m_rotation;

    Matrix3x4 m_transformMatrix;

    Vector3D m_forceAccum;

    Vector3D m_torqueAccum;

    public:

    void Integrate(float duration);

    void AddForce(const Vector3D& force);

    void AddForceAtPoint(const Vector3D& force, const Vector3D& pointMonde);

    void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& pointLocal);

    void ClearAccum();

    private:

    Vector3D worldPosition(const Vector3D& local)
    
};