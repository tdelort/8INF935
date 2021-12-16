#include "RigidBody.h"

#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix3x4.h"
#include "Matrix3x3.h"

#include <corecrt_math.h>
#include <math.h>

RigidBody::RigidBody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix3x3 tenseurInertie)
	: m_position(position), m_orientation(orientation), m_invMass(1/mass), m_damping(damping), m_angularDamping(angularDamping),
	m_forceAccum(Vector3D(0,0,0)), m_torqueAccum(Vector3D(0,0,0))
{
	m_invTenseurInertie = tenseurInertie.Inverse();
	CalculateDerivedData();
    onCollision = [](Contact* contact) {};
}

void RigidBody::Integrate(float duration)
{
    //Calcul de linearAcceleration
    Vector3D _linearAccel = m_invMass * m_forceAccum;
    Vector3D _angularAccel = m_inverseInertiaTensorWold * m_torqueAccum;
    
    //Update linear et angular velocity des Accel
    m_velocity += _linearAccel * duration;
    m_rotation += _angularAccel * duration;

    //Impose Drag 
    m_velocity *= pow(m_damping, duration);
    m_rotation *= pow(m_angularDamping, duration) ;

    //Met a jour la position
    m_position += m_velocity * duration;
    m_orientation.UpdateByAngularVelocity(m_rotation, duration); 
    // Normalise the orientation, and update the matrice
	CalculateDerivedData();
    // Clear accumulators.
    ClearAccum();
}
void RigidBody::AddForce(const Vector3D& force)
{
    m_forceAccum +=(force);
}

void RigidBody::AddForceAtPoint(const Vector3D& force, const Vector3D& pointMonde)
{
    AddForce(force);
    m_torqueAccum += Vector3D::cross(pointMonde - m_position, force);
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
    m_orientation.Normalize();
}

Vector3D RigidBody::GetPosition() const
{
    return m_position;
}

Vector3D RigidBody::GetRotation() const
{
    return m_orientation.Euler();
}

float RigidBody::GetInvMass() const
{
    return m_invMass;
}

Vector3D RigidBody::WorldPosition(const Vector3D& local)    
{
    return m_transformMatrix * local;
}

void RigidBody::CalculateDerivedData()
{
    m_transformMatrix.SetOrientationAndPosition(m_orientation, m_position);
    ComputeTenseurInertiaWorld(m_invTenseurInertie);
}

void RigidBody::ComputeTenseurInertiaWorld(Matrix3x3& inertiaTenseurWorld)
{
    // I-1' = Mb I-1 Mb-1
	Matrix3x3 transformMatrix3x3 = m_transformMatrix.ToMatrix3x3();
	m_inverseInertiaTensorWold = transformMatrix3x3 * m_invTenseurInertie;
	m_inverseInertiaTensorWold = m_inverseInertiaTensorWold * transformMatrix3x3.Inverse();
}