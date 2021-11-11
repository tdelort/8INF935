#pragma once    

#include "../Vector3D.h"
#include "../RigidBody.h"

class GravityForceGenerator : public ForceGenerator 
{
private: 
    Vector3D m_gravity;

public: 
    void UpdateForce (RigidBody* rigidBody);
};