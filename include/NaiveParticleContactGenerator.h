class NaiveParticleContactGenerator : public ParticleContactGenerator
    float radius;
    std::vector<Particle*> particles;
    unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};