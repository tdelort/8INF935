#pragma once

#include "ParticleLink.h"

class ParticleContact;

class ParticleCable : public Particlelink
{
public:
    float maxlength;
    float restitution;
    void AddContact(std::vector<ParticleContact*>* contacts) const override;
};