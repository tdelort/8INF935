#include "rigidbody_forces/SpringForceGenerator.h"
#include "RigidBody.h"
#include "Vector3D.h"

SpringForceGenerator::SpringForceGenerator(RigidBody* otherRigidBody, Vector3D otherBodyAnchor, Vector3D bodyAnchor, float k, float restingLength)
    : m_otherRigidBody(otherRigidBody), m_otherBodyAnchor(otherBodyAnchor), m_bodyAnchor(bodyAnchor), m_k(k), m_restingLength(restingLength)
{ }

void SpringForceGenerator::UpdateForce(RigidBody* rigidbody, float duration)
{
    Vector3D worldP1 = rigidbody->WorldPosition(m_bodyAnchor);
    Vector3D worldP2 = m_otherRigidBody->WorldPosition(m_otherBodyAnchor);

    Vector3D d = worldP1 - worldP2;
    Vector3D F = -m_k * (d.norm() - m_restingLength) * d.normalize();

    rigidbody->AddForceAtBodyPoint(F, m_bodyAnchor);
    m_otherRigidBody->AddForceAtBodyPoint(-F, m_otherBodyAnchor);
}