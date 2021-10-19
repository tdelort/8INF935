#pragma once

#include "ParticleContactGenerator.h"

class Particle;
class ParticleContact;

class Particlelink : public ParticleContactGenerator
{
public:
    Particle* particle[2];
    float currentLength() const;
    virtual void AddContact(std::vector<ParticleContact*>* contacts) const = 0;
};