class ParticleRod : public Particlelink
{
public:
    float length;
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};