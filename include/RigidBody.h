#pragma once

#include "Vector3D.h"

class RigidBody
{
    private:
    float m_angularDamping;

    Vector3D m_forceAccum;

    Vector3D m_torqueAccum;

    public:
    void AddForce(const Vector3D& force);

    void AddForceAtPoint(const Vector3D& force, const Vector3D& pointMonde);

    void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& pointLocal);

    void ClearAccum();

};