#include "particle_contacts/ParticleContact.h"
#include "Particle.h"


ParticleContact::ParticleContact(Particle* particle1, Particle* particle2)
{
    particle[2] = { particle1,particle2 };
}

ParticleContact::ParticleContact(Particle* particle1, Particle* particle2, float restitution = 1, float penetration)
    :restitution(restitution),penetration(penetration)
{
    particle[2]= {particle1,particle2};
}
void ParticleContact::resolve(float duration)
{
    resolveVelocity(duration);
    resolveInterpenetration(duration);
}
float ParticleContact::calculateSeparatingVelocity()
{
    Vector3 relativeVelocity = particle[0]->getVelocity();
    if (particle[1]) 
        relativeVelocity -= particle[1]->getVelocity();
    return relativeVelocity * contactNormal;
}
void ParticleContact::resolveVelocity(float duration)
{
    float k;
    if (particle[1])    //cas 1 : choc entre deux particules 
    {
        k = ((restitution + 1) * ((particle[0]->velocity() - particle[1]->velocity()) * contactNormal) / (particle[0]->invMass() + particle[1]->invMass());
        particle[1]->setVelocity(particle[1]->velocity() + k * contactNormal * particle[1]->invMass());
    }
    else                //cas 2 : choc entre particule et surface immuable
    {
        k = ((restitution + 1) * (particle[0]->velocity() * contactNormal)) / (particle[0]->invMass());
    }

    particle[0]->setVelocity(particle[0]->velocity() + k * contactNormal * particle[0]->invMass());
}
void ParticleContact::resolveInterpenetration(float duration)
{
    if (particle[1])    // cas 1 : choc entre deux particules
    {   //TODO : mettre une getter sur la masse d'une particule
        particle[1]->setPosition(particle[1]->position() + (-(1 / particle[0]->invMass()) / ((1 / particle[0]->invMass()) + (1 / particle[1]->invMass())) * penetration * contactNormal));
        particle[0]->setPosition(particle[0]->position() + ((1 / particle[1]->invMass()) / ((1 / particle[0]->invMass()) + (1 / particle[1]->invMass())) * penetration * contactNormal));
    }
    else                // cas 2 : choc entre particule et surface immuable
    {
        particle[0]->setPosition(particle[0]->position() + penetration * contactNormal);
    }
}