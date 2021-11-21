#include "RigidBody.h"

void RigidBody::Integrate(float duration)
{
    
}
void RigidBody::AddForce(const Vector3D& force)
{
    m_forceAccum += force;
}

void RigidBody::addForceAtPoint(const Vector3D& force, const Vector3D& pointMonde)
{
    addForce(force);
    m_torqueAccum += (m_position - pointMonde) * force;
}

void RigidBody::AddForceAtBodyPoint(const Vector3D& force, const Vector3D& pointLocal)
{
    Vector3D world = WorldPosition(pointLocal);
    AddForceAtPoint(force, wolrd);
}

void RigidBody::ClearAccumulator()
{
    m_forceAccum = Vector3D(0,0,0);
    m_torqueAccum = Vector3D(0,0,0);
}

Vector3D RigidBody::GetPosition() const
{
    return m_position;
}

Vector3D RigidBody::GetRotation() const
{
    return m_orientation.Euler();
}

Vector3D RigidBody::WorldPosition(const Vector3D& local)    
{
    return m_transformMtrix.Inverse()*local;
}