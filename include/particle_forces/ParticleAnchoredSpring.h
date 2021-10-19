#pragma once

#include "ParticleForceGenerator.h"
#include "../Vector3D.h"

class ParticleAnchoredSpring : public ParticleForceGenerator
{

private:
    //other anchor
    Vector3D m_anchor; 

    //Spring constant
    float m_k;
    float m_restLength;

public:
    void UpdateForce(Particle* particle, float duration);
};
