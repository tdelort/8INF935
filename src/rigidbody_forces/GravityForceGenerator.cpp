#include "../../include/forces/GravityForceGenerator.h"
#include "../../include/RigidBody.h"
#include "../../include/Vector3D.h"


GravityForceGenerator::GravityForceGenerator(Vector3D gravity)
    : m_gravity(gravity)
{

}

void GravityForceGenerator::UpdateForce(RigidBody* rigidBody)
{
    Vector3D F = (1.0 / rigidBody->invMass()) * m_gravity;
    rigidBody->addForce(F);
}