#include "particle_contacts/ParticleCable.h"
#include "Particle.h"

void ParticleCable::AddContact(std::vector<ParticleContact*>* contacts) const
{
	if (currentLength() > maxlength)
	{
		contacts->push_back(new ParticleContact(particle[0], particle[1], 0, currentLength()- maxlength));
	}
}
