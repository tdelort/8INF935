#pragma once

#include "../Vector3D.h"

class Particle;

class ParticleContact
{
public:

    Particle* particle[2];

    float restitution;
    float penetration;
    Vector3D contactNormal;
    ParticleContact(Particle* particle1, Particle* particle2);
    ParticleContact(Particle* particle1, Particle* particle2, float restitution, float penetration);
    void resolve(float duration);
    float calculateSeparatingVelocity();

private:

    void resolveVelocity(float duration);
    void resolveInterpenetration(float duration);
};