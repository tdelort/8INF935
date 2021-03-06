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
    ParticleAnchoredSpring(float k, float restLength, const Vector3D& anchor);

    void UpdateForce(Particle* particle, float duration) override;
    void SetK(float k);
    void SetRestLength(float restLength);
    void SetAnchor(const Vector3D& anchor);
};
