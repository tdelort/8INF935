class ParticleCable : public Particlelink
{
public:
    float maxlength;
    float restitution;
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};