#pragma once

#include <vector>

class ParticleContact;

class ParticleContactResolver
{
protected:
    unsigned int iteration;

public:
    void resolveContacts(std::vector<ParticleContact*>* contacts, float duration);
};