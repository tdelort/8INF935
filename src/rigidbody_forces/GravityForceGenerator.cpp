#include "rigidbody_forces/GravityForceGenerator.h"
#include "RigidBody.h"
#include "Vector3D.h"


GravityForceGenerator::GravityForceGenerator(Vector3D gravity)
    : m_gravity(gravity)
{ }

void GravityForceGenerator::UpdateForce(RigidBody* rigidBody, float duration)
{
    Vector3D F = (1.0 / rigidBody->GetInvMass()) * m_gravity;
    rigidBody->AddForce(F);
}