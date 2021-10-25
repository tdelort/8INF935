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

public:
    Registry m_registry;

    void UpdateForce(float duration);
    void AddEntry(Particle* p, ParticleForceGenerator* generator);
};