#pragma once

#include "ParticleForceGenerator.h"

#include "../Vector3D.h"

class Particle;

class ParticleGravity: public ParticleForceGenerator
{
    Vector3D m_gravity;

public:
    ParticleGravity(Vector3D gravity);
    void UpdateForce (Particle* particle, float duration);
    void SetGravity(const Vector3D& gravity);
};


