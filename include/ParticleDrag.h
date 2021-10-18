#pragma once

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"

class ParticleDrag: public ParticleForceGenerator
{
private:
// drag coeffiecents
    float m_k1;
    float m_k2;
public:
    void UpdateForce (Particle* particle, float duration);
// apply simplified drag based on particle's velocity 
};