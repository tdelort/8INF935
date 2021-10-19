#include "particle_forces/ParticleDrag.h"
#include "Particle.h"

void ParticleDrag::UpdateForce (Particle* particle, float duration)
{
    Vector3D v = particle->velocity();
    double norm = v.norm();
    if(norm > 0)
    {
        Vector3D F = -v.normalize() * (m_k1 * norm + m_k2 * norm * norm);
        particle->addForce(F);
    }
}

void ParticleDrag::SetK1(float k1)
{
    m_k1 = k1;
}

void ParticleDrag::SetK2(float k2)
{
    m_k2 = k2;
}