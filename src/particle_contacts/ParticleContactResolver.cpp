#include "particle_contacts/ParticleContactResolver.h"
#include "particle_contacts/ParticleContact.h"
#include "Particle.h"

void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*>* contacts, float duration)
{
	//On r�soud le contact avec la plus petite velocit� relative en premier 
	if (contacts->empty())
		return;
	float sRelativeVelocity = contacts->at(0)->calculateSeparatingVelocity();
	int iContact = 0, nbIteration = 0;
	while (nbIteration < 2) { //deux it�rations de la liste possible
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
