#include "particle_forces/ParticleForceRegistry.h"
#include "Particle.h"

#include <vector>
#include <algorithm>

void ParticleForceRegistry::UpdateForce(float duration)
{
    for(int i = 0; i < m_registry.size(); i ++)
    {
        m_registry[i].forceGenerator->UpdateForce(m_registry[i].particle, duration);
    }
}

void ParticleForceRegistry::AddEntry(Particle* p, ParticleForceGenerator* generator)
{
    m_registry.push_back({p, generator});
}