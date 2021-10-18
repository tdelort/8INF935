#pragma once

#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "Vector3D.h"


class ParticleGravity: public ParticleForceGenerator
{

    Vector3D m_gravity;

    public:

    // F = particle->GetMass()*m_gravity

    void UpdateForce (Particle* particle, float duration);
    
};


