#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Particle.h"
#include "particle_forces/ParticleForceRegistry.h"
#include "particle_forces/ParticleForceGenerator.h"
#include "particle_contacts/ParticleContactGenerator.h"
#include "particle_contacts/ParticleContactResolver.h"

#include "RigidBody.h"
#include "rigidbody_forces/RigidBodyForceRegistry.h"

#include "GameObject.h"
#include "rigidbody_contacts/CollisionDetector.h"
#include "colliders/Primitive.h"

#include "OcTree.h"

class  PhysicsEngine
{
private:
    std::vector<Particle*> particles;
    ParticleForceRegistry particleForceRegistry;
    std::vector<ParticleContactGenerator*> particleContactGenerators;
    ParticleContactResolver particleContactResolver;

    std::vector<GameObject*> gameObjects;
    RigidBodyForceRegistry rigidBodyForceRegistry;

    OcTree octree;

    void ResolveForces(float dt);
    void ResolveCollisions(float dt);
    void ResolveCollisionsParticles(float dt);
    void ResolveCollisionsRigidBodies(float dt);

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
    static void AddParticleForceGenerator(Particle* p, ParticleForceGenerator* particleForceGenerator);
    static void AddParticleContactGenerator(ParticleContactGenerator* particleContactGenerator);

    static void AddGameObject(GameObject* obj);
    static void AddRigidBodyForceGenerator(RigidBody* rb, ForceGenerator* forceGenerator);

    static void Update(float dt);

    static void Clear();

    static std::vector<Particle*> GetParticles();
    static std::vector<GameObject*> GetGameObjects();
#ifdef OCTREE_DEBUG
    static void DrawOctree();
#endif
};

// Add things
void PhysicsEngine::AddParticle(Particle* particle)
{
    instance().particles.push_back(particle);
}

void PhysicsEngine::AddGameObject(GameObject* gameObject)
{
    instance().gameObjects.push_back(gameObject);
}

void PhysicsEngine::AddParticleForceGenerator(Particle* p, ParticleForceGenerator* particleForceGenerator)
{
    instance().particleForceRegistry.AddEntry(p, particleForceGenerator);
}

void PhysicsEngine::AddParticleContactGenerator(ParticleContactGenerator* particleContactGenerator)
{
    instance().particleContactGenerators.push_back(particleContactGenerator);
}

void PhysicsEngine::AddRigidBodyForceGenerator(RigidBody* rb, ForceGenerator* forceGenerator)
{
    instance().rigidBodyForceRegistry.AddEntry(rb, forceGenerator);
}

// Update things
void PhysicsEngine::Update(float dt)
{

    instance().ResolveForces(dt);
    
    for(auto& particle : instance().particles)
        particle->Integrate(dt);

    for(auto& obj : instance().gameObjects)
        obj->rb->Integrate(dt);

    instance().ResolveCollisions(dt);
}

void PhysicsEngine::Clear()
{
    // No delete
    instance().particles.clear();
    instance().particleForceRegistry = ParticleForceRegistry();
    instance().particleContactGenerators.clear();
    instance().gameObjects.clear();
    instance().rigidBodyForceRegistry = RigidBodyForceRegistry();
}

// Get things
std::vector<Particle*> PhysicsEngine::GetParticles()
{
    return instance().particles;
}

std::vector<GameObject*> PhysicsEngine::GetGameObjects()
{
    return instance().gameObjects;
}


// Private functions
void PhysicsEngine::ResolveForces(float dt)
{
    // For particles
    particleForceRegistry.UpdateForce(dt);

    // For rigid bodies
    rigidBodyForceRegistry.UpdateForce(dt);
}

void PhysicsEngine::ResolveCollisions(float dt)
{
    ResolveCollisionsParticles(dt);
    ResolveCollisionsRigidBodies(dt);
}

void PhysicsEngine::ResolveCollisionsParticles(float dt)
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

void PhysicsEngine::ResolveCollisionsRigidBodies(float dt)
{
    instance().octree = OcTree(Vector3D(0, 0, 0), Vector3D(3, 3, 3));

    for(auto& obj : instance().gameObjects)
        instance().octree.Insert(obj->collider);

    std::vector<Contact*> rigidBodyContacts;

    std::vector<Primitive*> done;

    for(auto& obj : instance().gameObjects)
    {
        std::vector<Primitive*> queryResults = instance().octree.Query(obj->collider);

        for(auto& otherCol : queryResults)
        {
            if(obj->collider == otherCol)
                continue;

            // If the other collider was already checked, skip it
            if(std::find(done.begin(), done.end(), otherCol) != done.end())
                continue;
            
            // Narrow phase
            CollisionDetector::generateContacts(*obj->collider, *otherCol, &rigidBodyContacts);
        }

        done.push_back(obj->collider);
    }

    if(rigidBodyContacts.size() > 0)
    {
        std::cout << "Collision detected!" << std::endl;
    }
}

void PhysicsEngine::DrawOctree()
{
    instance().octree.Draw();
}