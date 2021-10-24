#pragma once

#include "ParticleForceGenerator.h"

class Particle;

class ParticleSpring : public ParticleForceGenerator
{
private:
    //other anchor
    Particle* m_other;

    //Spring constant
    float m_k;

    float m_restLength;

public:

    ParticleSpring(float k, float restLength, Particle* other);

    void UpdateForce(Particle* particle, float duration) override;
    void SetK(float k);
    void SetRestLength(float restLength);
    void SetParticle(Particle* other);
};
