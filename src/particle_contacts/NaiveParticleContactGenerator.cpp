#include "particle_contacts/NaiveParticleContactGenerator.h"
#include "particle_contacts/ParticleContact.h"
#include "Particle.h"

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float radius, std::vector<Particle*> particles)
	:radius(radius), particles(particles)
{
}

void NaiveParticleContactGenerator::AddContact(std::vector<ParticleContact*>* contacts) const
{
	for (int i = 0; i < particles.size()-1; i++)
	{
		for (int j = i+1; j < particles.size(); j++)
		{
			float distance = (float)(particles[i]->position() - particles[j]->position()).norm();
			if (distance < radius)
			{
				contacts->push_back(new ParticleContact(particles[i], particles[j], 1, radius - distance));
			}
		}
	}
}


