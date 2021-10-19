#pragma once

#include "ParticleForceGenerator.h"

#include <vector>

class Particle;

class ParticleForceRegistry
{
private:

    struct ParticleForceEntry
    {
        Particle* particle;
        ParticleForceGenerator* forceGenerator;
    };

    using Registry = std::vector<ParticleForceEntry>; 
    Registry m_registry;

public:

    void UpdateForce(float duration);
};