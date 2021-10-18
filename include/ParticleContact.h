#pragma once

#include "Particle.h"
#include "Vector3D.h"

class ParticleContact
{
public:

    Particle* particle[2];

    float restitution;
    float penetration;
    Vector3D contactNormal;

    void resolve(float duration);
    float calculateSeparatingVelocity();

private:

    void resolveVelocity();
    void resolveInterpenetration();
};