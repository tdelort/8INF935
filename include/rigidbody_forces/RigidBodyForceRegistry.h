#pragma once

#include "ForceGenerator.h"

#include <vector>

class RigidBody;

class RigidBodyForceRegistry
{
private:

    struct ForceEntry
    {
        RigidBody* rb;
        ForceGenerator* forceGenerator;
    };

    using Registry = std::vector<ForceEntry>; 

public:
    Registry m_registry;

    void UpdateForce(float duration);
    void AddEntry(RigidBody* rb, ForceGenerator* generator);
};