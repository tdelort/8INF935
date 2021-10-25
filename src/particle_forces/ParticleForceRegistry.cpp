#include "particle_forces/ParticleForceRegistry.h"
#include "Particle.h"

#include <vector>
#include <algorithm>

void ParticleForceRegistry::UpdateForce(float duration)
{
    // NOTE : Clears some particles multiple times
    // Not a bug, but it is useless
    //std::for_each(m_registry.begin(), m_registry.end(), 
    //    [duration](ParticleForceEntry entry)
    //    {
    //        entry.particle->clearForces();
    //    }
    //);

    std::for_each(m_registry.begin(), m_registry.end(), 
        [duration](ParticleForceEntry entry)
        {
            entry.forceGenerator->UpdateForce(entry.particle, duration);
        }
    );
}

void ParticleForceRegistry::AddEntry(Particle* particle, ParticleForceGenerator* generator)
{
    m_registry.push_back({particle, generator});
}