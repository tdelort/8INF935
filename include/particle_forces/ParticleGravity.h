#pragma once

#include "ParticleForceGenerator.h"

#include "../Vector3D.h"

class Particle;

class ParticleGravity: public ParticleForceGenerator
{
    Vector3D m_gravity;

public:
    // F = particle->GetMass()*m_gravity
    void UpdateForce (Particle* particle, float duration);
    void SetGravity(const Vector3D& gravity);
};


