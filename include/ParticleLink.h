class Particlelink : public ParticleContactGenerator
{
public:
    Particle* particle[2];
    float currentLength() const;
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};