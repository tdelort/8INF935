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
    ParticleBungeeSpring(float k, float restLength, Particle* other);

    void UpdateForce(Particle* particle, float duration) override;
    void SetK(float k);
    void SetRestLength(float restLength);
    void SetParticle(Particle* other);
};
