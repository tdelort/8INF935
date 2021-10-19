#pragma once
#include <vector>

class ParticleContact;

class ParticleContactGenerator
{
public:
    virtual void AddContact(std::vector<ParticleContact*>* contacts) const = 0;
};