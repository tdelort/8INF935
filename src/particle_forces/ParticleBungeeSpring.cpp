#include "Particle.h"
#include "particle_forces/ParticleBungeeSpring.h"

void ParticleBungeeSpring::UpdateForce(Particle* particle, float duration)
{
    Vector3D d = particle->position() - m_other->position();
    if(d.norm() - m_restLength > 0)
    {
        Vector3D F = -m_k * (d.norm() - m_restLength) * d.normalize();
        particle->addForce(F);
    }
}

ParticleBungeeSpring::ParticleBungeeSpring(float k, float restLength, Particle* other)
    : m_k(k), m_restLength(restLength), m_other(other)
{}

void ParticleBungeeSpring::SetK(float k)
{
    m_k = k;
}

void ParticleBungeeSpring::SetRestLength(float restLength)
{
    m_restLength = restLength;
}

void ParticleBungeeSpring::SetParticle(Particle* other)
{
    m_other = other;
}

