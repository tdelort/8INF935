#include "../../include/forces/GravityForceGenerator.h"
#include "../../include/RigidBody.h"
#include "../../include/Vector3D.h"

void ParticleSpring::UpdateForce(RigidBody* rigidbody)
{
    Vector3D d = rigidbody->position() - m_otherRigidBody->position();
    Vector3D F = -m_k * (d.norm() - m_restingLength) * d.normalize();
    RigidBody->AddForce(F);
    m_otherRigidBody->AddForce(-F);
}