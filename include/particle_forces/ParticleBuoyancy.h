#pragma once

#include "ParticleForceGenerator.h"

class Particle;

class ParticleBuoyancy : public ParticleForceGenerator
{
private:

    //particle properties
    float m_maxDepth;
    float m_volume;

    //effect properties
    float m_waterHeight;
    float m_liquidDensity;

public:
    void UpdateForce(Particle* particle, float duration);
};