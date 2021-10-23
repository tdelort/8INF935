#pragma once

#include "ParticleContactGenerator.h"

class Particle;
class ParticleContact;

class NaiveParticleContactGenerator : public ParticleContactGenerator
{
    float radius;
    std::vector<Particle*> particles;

    NaiveParticleContactGenerator(float radius, std::vector<Particle*> particles);

    void AddContact(std::vector<ParticleContact*>* contacts) const override;
};