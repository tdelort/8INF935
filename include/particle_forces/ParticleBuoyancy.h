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
    ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity);
    void UpdateForce(Particle* particle, float duration);
    void SetMaxDepth(float maxDepth);
    void SetVolume(float volume);
    void SetWaterHeight(float waterHeight);
    void SetLiquidDensity(float liquidDensity);
};