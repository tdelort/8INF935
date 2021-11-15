#include "RigidBody.h"

void RigidBody::Integrate(float duration)
{
    
}
void RigidBody::AddForce(const Vector3D& force)
{
    m_forceAccum +=(force);
}

void RigidBody::AddForceAtPoint(const Vector3D& force, const Vector3D& pointMonde)
{
    AddForce(force);
    m_torqueAccum += (m_position - pointMonde).dot(force);
}

void RigidBody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& pointLocal)
{
    Vector3D world = WorldPosition(pointLocal);
    AddForceAtPoint(force, world);
}

void RigidBody::ClearAccum()
{
    m_forceAccum = Vector3D(0,0,0);
    m_torqueAccum = Vector3D(0,0,0);
}

Vector3D RigidBody::WorldPosition(const Vector3D& local)    
{
    return m_transformMatrix.Inverse()*local;
}