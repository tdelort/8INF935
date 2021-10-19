#include "particle_forces/ParticleGravity.h"

#include "Vector3D.h"
#include "Particle.h"

ParticleGravity::ParticleGravity(Vector3D gravity)
    : m_gravity(gravity)
{}

void ParticleGravity::UpdateForce(Particle* particle, float duration)
{
    Vector3D F = (1.0 / particle->invMass()) * m_gravity;
    particle->addForce(F);
}

void ParticleGravity::SetGravity(const Vector3D& gravity)
{
    m_gravity = gravity;
}
