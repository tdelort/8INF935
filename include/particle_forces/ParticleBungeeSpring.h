#pragma once

#include "ParticleForceGenerator.h"

class Particle;

class ParticleBungeeSpring : public ParticleForceGenerator
{
private:
    //other anchor
    Particle* m_other;

    //Spring constant
    float m_k;

    float m_restLength;
    // Calcul uniquement lorsque la distance entre les deux encrages est > à m_restLength

public:

    void UpdateForce(Particle* particle, float duration);
};
