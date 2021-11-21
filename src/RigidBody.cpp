#include "RigidBody.h"
#include <corecrt_math.h>
#include <math.h>

Rigidbody::Rigidbody(Vector3D position, Quaternion orientation, float mass, float damping, float angularDamping, Matrix33 tenseurInertie) : 
	m_position(position), m_orientation(orientation), m_inverseMass(1/mass), m_damping(damping), m_angularDamping(angularDamping),
	m_forceAccum(Vector3D(0,0,0)), m_torqueAccum(Vector3D(0,0,0))
{
	CalculateDerivedData();
	m_invTenseurInertie = tenseurInertie.Inverse();
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
    m_velocity *= pow(m_damping, duration) 
    m_rotation *= pow(m_amgularDamping, duration) ;

    //Met a jour la position
    m_position += m_velocity * duration;
    m_orientation.UpdateByAngularVelocity(m_rotation, duration); 
    // Normalise the orientation, and update the matrice
    calculateWorldLocalData();
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

void RigidBody::CalculateDerivedData()
{
    m_transformMatrix.SetOrientationAndPosition(m_orientation, m_position);
    // ComputeTenseurInertiaWorld(m_invTenseurInertie)
}

void Rigidbody::ComputeTenseurInertiaWorld(Matrix3x3& inertiaTenseurWorld)
{
	// Matrix3x3 transformMatrix3x3 = m_transformMatrix.ToMatrix3x3();
	// inertiaTenseurWorld = transformMatrix3x3 * m_invTenseurInertie;
	// inertiaTenseurWorld *= transformMatrix3x3.Inverse();
}