#include "rigidbody_forces/RigidBodyForceRegistry.h"
#include "RigidBody.h"

#include <vector>
#include <algorithm>

void RigidBodyForceRegistry::UpdateForce(float duration)
{
    for(int i = 0; i < m_registry.size(); i ++)
    {
        m_registry[i].forceGenerator->UpdateForce(m_registry[i].rb, duration);
    }
}

void RigidBodyForceRegistry::AddEntry(RigidBody* rb, ForceGenerator* generator)
{
    m_registry.push_back({rb, generator});
}