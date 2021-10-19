#pragma once

#include "ParticleLink.h"

class Particle;
class ParticleContact;

class ParticleRod : public Particlelink
{
public:
    float length;
    void AddContact(std::vector<ParticleContact*>* contacts) const override;
};