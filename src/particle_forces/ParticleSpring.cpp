#include "particle_forces/ParticleSpring.h"
#include "Particle.h"

void ParticleSpring::UpdateForce(Particle* particle, float duration)
{
    Vector3D d = particle->position() - m_other->position();
    Vector3D F = -m_k * (d.norm() - m_restLength) * d.normalize();
    particle->addForce(F);
    m_other->addForce(-F);
}

ParticleSpring::ParticleSpring(float k, float restLength, Particle* other)
    : m_k(k), m_restLength(restLength)
{
    m_other = other;
}

void ParticleSpring::SetK(float k)
{
    m_k = k;
}

void ParticleSpring::SetRestLength(float restLength)
{
    m_restLength = restLength;
}

void ParticleSpring::SetParticle(Particle* other)
{
    m_other = other;
}

