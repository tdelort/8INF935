#pragma once    

#include "../Vector3D.h"
#include "../RigidBody.h"
#include "ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator 
{
private: 
    Vector3D m_gravity;

public: 
    GravityForceGenerator(Vector3D gravity);
    void UpdateForce (RigidBody* rigidBody, float duration);
};