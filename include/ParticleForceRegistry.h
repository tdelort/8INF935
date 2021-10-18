#pragma once

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

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

    //... Registry Accessors

    void UpdateForce(float duration);
};