#pragma once

#include "../RigidBody.h"

class ForceGenerator
{
    public: 
    virtual void UpdateForce (RigidBody* rigidBody, float duration) = 0;
};