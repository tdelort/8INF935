#include "particle_contacts/ParticleContactResolver.h"
#include "particle_contacts/ParticleContact.h"
#include "Particle.h"

void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*>* contacts, float duration)
{
	//On resoud le contact avec la plus petite velocite relative en premier 
	if (contacts->empty())
		return;
	float sRelativeVelocity = contacts->at(0)->calculateSeparatingVelocity();
	int iContact = 0, nbIteration = 0;
	while (nbIteration < contacts->size())  { 
		for (int i = 0; i < contacts->size(); i++)
		{
			float iRelativeVelocity = contacts->at(i)->calculateSeparatingVelocity();
			if (sRelativeVelocity > iRelativeVelocity)
			{
				sRelativeVelocity = iRelativeVelocity;
				iContact = i;
			}
		}
		contacts->at(iContact)->resolve(duration);
		nbIteration++;
	}
}
