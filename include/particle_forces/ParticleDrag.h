#pragma once

#include "ParticleForceGenerator.h"

class Particle;

class ParticleDrag: public ParticleForceGenerator
{
private:
// drag coeffiecents
    float m_k1;
    float m_k2;
public:
    void UpdateForce (Particle* particle, float duration);
// apply simplified drag based on particle's velocity 
// F = - P (m_k1 * norme(p) + m_k2 * norme(p)^2)
};