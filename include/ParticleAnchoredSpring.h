class ParticleAnchoredSpring : public ParticleForceGenerator
{

private:
    //other anchor
    Vectorr3 m_anchor; 

    //Spring constant
    float m_k;
    float m_restLength;

public:
    void UpdateForce(Particle* particle, float duration);
};
