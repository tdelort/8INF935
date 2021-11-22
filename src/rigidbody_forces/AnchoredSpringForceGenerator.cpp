#include "rigidbody_forces/AnchoredSpringForceGenerator.h"
#include "RigidBody.h"
#include "Vector3D.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector3D anchor, Vector3D bodyAnchor, float k, float restingLength)
    : m_anchor(anchor), m_bodyAnchor(bodyAnchor), m_k(k), m_restingLength(restingLength)
{ }

void AnchoredSpringForceGenerator::UpdateForce(RigidBody* rigidbody, float duration)
{
    Vector3D worldP1 = rigidbody->WorldPosition(m_bodyAnchor);

    Vector3D d = worldP1 - m_anchor;
    Vector3D F = -m_k * (d.norm() - m_restingLength) * d.normalize();
    rigidbody->AddForceAtBodyPoint(F, m_bodyAnchor);
}