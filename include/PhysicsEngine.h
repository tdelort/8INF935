#pragma once

#include <vector>
#include <iostream>

#include "Particle.h"
#include "RigidBody.h"
#include "particle_forces/ParticleForceRegistry.h"
#include "particle_forces/ParticleForceGenerator.h"
#include "particle_contacts/ParticleContactGenerator.h"
#include "particle_contacts/ParticleContactResolver.h"

class  PhysicsEngine
{
private:
    std::vector<Particle*> particles;
    ParticleForceRegistry particleForceRegistry;
    std::vector<ParticleContactGenerator*> particleContactGenerators;
    ParticleContactResolver particleContactResolver;

    std::vector<RigidBody*> rigidBodies;

    void ResolveForces(float dt);
    void ResolveCollisions(float dt);

    PhysicsEngine() = default;

public:
    PhysicsEngine(const PhysicsEngine&) = delete;
    PhysicsEngine& operator=(const PhysicsEngine&) = delete;
    PhysicsEngine(const PhysicsEngine&& ) = delete;
    PhysicsEngine& operator=(const PhysicsEngine&& ) = delete;

    static PhysicsEngine& instance()
    {
        static PhysicsEngine instance;
        return instance;
    }

    static void AddParticle(Particle* particle);
    static void AddRigidBody(RigidBody* rigidBody);
    static void AddParticleForceGenerator(Particle* p, ParticleForceGenerator* particleForceGenerator);
    static void AddParticleContactGenerator(ParticleContactGenerator* particleContactGenerator);

    static void Update(float dt);

    static void Clear();

    static std::vector<Particle*> GetParticles();
    static std::vector<RigidBody*> GetRigidBodies();
};

// Add things
void PhysicsEngine::AddParticle(Particle* particle)
{
    instance().particles.push_back(particle);
}

void PhysicsEngine::AddRigidBody(RigidBody* rigidBody)
{
    instance().rigidBodies.push_back(rigidBody);
}

void PhysicsEngine::AddParticleForceGenerator(Particle* p, ParticleForceGenerator* particleForceGenerator)
{
    instance().particleForceRegistry.AddEntry(p, particleForceGenerator);
}

void PhysicsEngine::AddParticleContactGenerator(ParticleContactGenerator* particleContactGenerator)
{
    instance().particleContactGenerators.push_back(particleContactGenerator);
}


// Update things
void PhysicsEngine::Update(float dt)
{

    instance().ResolveForces(dt);
    
    for(auto& particle : instance().particles)
        particle->Integrate(dt);

    for(auto& rigidBody : instance().rigidBodies)
        rigidBody->Integrate(dt);

    instance().ResolveCollisions(dt);
}

void PhysicsEngine::Clear()
{
    // No delete
    instance().particles.clear();
    instance().particleForceRegistry = ParticleForceRegistry();
    instance().particleContactGenerators.clear();
    instance().rigidBodies.clear();
}

// Get things
std::vector<Particle*> PhysicsEngine::GetParticles()
{
    return instance().particles;
}

std::vector<RigidBody*> PhysicsEngine::GetRigidBodies()
{
    return instance().rigidBodies;
}


// Private functions
void PhysicsEngine::ResolveForces(float dt)
{
    // For particles
    particleForceRegistry.UpdateForce(dt);

    // For rigid bodies
}

void PhysicsEngine::ResolveCollisions(float dt)
{
    std::vector<ParticleContact*> particleContacts;

    // Generate contacts
    for(auto& particleContactGenerator : instance().particleContactGenerators)
        particleContactGenerator->AddContact(&particleContacts);

    // Resolve contacts
    instance().particleContactResolver.resolveContacts(&particleContacts, dt);
    
    // free memory allocated by particleContacts
    for(auto& particleContact : particleContacts)
        delete particleContact;
}