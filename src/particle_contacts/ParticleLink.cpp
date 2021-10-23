#include "particle_contacts/ParticleLink.h"
#include "Particle.h"

float Particlelink::currentLength() const
{
	return (particle[0]->position() - particle[1]->position()).norm();
}
