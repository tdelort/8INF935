#pragma once

class Particle;

class ParticleForceGenerator
{
public:
    virtual void UpdateForce(Particle* particle, float duration) = 0;
};