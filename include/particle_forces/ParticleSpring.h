#pragma once

#include "ParticleForceGenerator.h"
#include "../Particle.h"


class ParticleSpring : public ParticleForceGenerator
{
private:
    //other anchor

    //Spring constant
    float m_k;

    float m_restLength;

public:
    Particle* m_other;

    ParticleSpring(float k, float restLength, Particle* other);

    void UpdateForce(Particle* particle, float duration) override;
    void SetK(float k);
    void SetRestLength(float restLength);
    void SetParticle(Particle* other);
};
