#include "particle_contacts/ParticleRod.h"
#include "Particle.h"

void ParticleRod::AddContact(std::vector<ParticleContact*>* contacts) const
{
	if (currentLength() < length)
	{
		contacts->push_back(new ParticleContact(particle[0], particle[1], 0 , length - currentLength()))
	}
	else if (currentLength() > length)
	{
		contacts->push_back(new ParticleContact(particle[0], particle[1], 0, currentLength() - length))
	}
}
