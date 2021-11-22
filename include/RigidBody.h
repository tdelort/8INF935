#pragma once

#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix3x4.h"
#include "Matrix3x3.h"

class RigidBody
{
    private:
    float m_invMass;
    float m_damping;
    float m_angularDamping;
    Vector3D m_velocity;
    Vector3D m_position;

    Quaternion m_orientation;

    Vector3D m_rotation;

    Matrix3x4 m_transformMatrix;

    Matrix3x3 m_invTenseurInertie;

    Matrix3x3 m_inverseInertiaTensorWold;

    Vector3D m_forceAccum;

    Vector3D m_torqueAccum;

    public:

    RigidBody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix3x3 tenseurInertie);

    void Integrate(float duration);

    void AddForce(const Vector3D& force);

    void AddForceAtPoint(const Vector3D& force, const Vector3D& pointMonde);

    void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& pointLocal);

    void ClearAccum();

    Vector3D GetPosition() const;

    Vector3D GetRotation() const;

    float GetInvMass() const;

    Vector3D WorldPosition(const Vector3D& local);

    private:
    void CalculateDerivedData();
    void ComputeTenseurInertiaWorld(Matrix3x3 &inertiaTenseur);
    
};