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
    ParticleDrag(float k1, float k2);
    void UpdateForce (Particle* particle, float duration);
    void SetK1(float k1);
    void SetK2(float k2);
};