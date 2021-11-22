#pragma  once

#include "../Vector3D.h"
#include "../RigidBody.h"
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
private:

    Vector3D m_bodyAnchor;

    RigidBody* m_otherRigidBody = nullptr;
    Vector3D m_otherBodyAnchor;

    float m_k;
    float m_restingLength;

public: 

    SpringForceGenerator(RigidBody* otherRigidBody, Vector3D otherBodyAnchor, Vector3D bodyAnchor, float k, float restingLength);
    void UpdateForce(RigidBody* rigidBody, float duration) override; 

};