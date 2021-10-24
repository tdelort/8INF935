#include "Particle.h"
#include "particle_forces/ParticleBuoyancy.h"

ParticleBuoyancy::ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity)
    : m_maxDepth(maxDepth), m_volume(volume), m_waterHeight(waterHeight), m_liquidDensity(liquidDensity)
{ }

void ParticleBuoyancy::UpdateForce(Particle* particle, float duration)
{
    float d = particle->position().y() - m_waterHeight - m_maxDepth;
    d /= 2 * m_maxDepth;
    if(d >= 1)
        particle->addForce(Vector3D(0, m_volume * m_liquidDensity, 0));
    else if (d > 0)
        particle->addForce(Vector3D(0, d * m_volume * m_liquidDensity, 0));
}

void ParticleBuoyancy::SetMaxDepth(float maxDepth)
{
    m_maxDepth = maxDepth;
}

void ParticleBuoyancy::SetVolume(float volume)
{
    m_volume;
}

void ParticleBuoyancy::SetWaterHeight(float waterHeight)
{
    m_waterHeight = waterHeight;
}

void ParticleBuoyancy::SetLiquidDensity(float liquidDensity)
{
    m_liquidDensity = liquidDensity;
}