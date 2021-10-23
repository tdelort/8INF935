#include "particle_contacts/ParticleContactResolver.h"
#include "Particle.h"

void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*>* contacts, float duration)
{
	//On résoud le contact avec la plus petite velocité relative en premier 
	if (contacts->empty())
		return;
	float sRelativeVelocity = contacts[0]->calculateSeparatingVelocity();
	int iContact = 0, nbIteration = 0;
	while (nbIteration < 2) { //deux itérations de la liste possible
		for (int i = 0; i < contacts.size(); i++)
		{
			float iRelativeVelocity = contacts[i]->calculateSeparatingVelocity()
				if (sRelativeVelocity > iRelativeVelocity)
				{
					sRelativeVelocity = iRelativeVelocity;
					iContact = i;
				}
		}
		contacts[iContact]->resolve(duration);
		nbIteration++;
	}
}
