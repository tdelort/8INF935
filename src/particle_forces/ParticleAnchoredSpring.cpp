#include "Particle.h"
#include "particle_forces/ParticleAnchoredSpring.h"
#include "Vector3D.h"

ParticleAnchoredSpring::ParticleAnchoredSpring(float k, float restLength, const Vector3D& anchor)
    : m_k(k), m_restLength(restLength), m_anchor(anchor)
{}

void ParticleAnchoredSpring::UpdateForce(Particle* particle, float duration)
{
    Vector3D d = particle->position() - m_anchor;
    Vector3D F = -m_k * (d.norm() - m_restLength) * d.normalize();
    particle->addForce(F);
}

void ParticleAnchoredSpring::SetK(float k)
{
    m_k = k;
}

void ParticleAnchoredSpring::SetRestLength(float restLength)
{
    m_restLength = restLength;
}

void ParticleAnchoredSpring::SetAnchor(const Vector3D& anchor)
{
    m_anchor = anchor;
}
