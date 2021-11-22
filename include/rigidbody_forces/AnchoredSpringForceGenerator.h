#pragma  once

#include "../Vector3D.h"
#include "../RigidBody.h"
#include "ForceGenerator.h"

class AnchoredSpringForceGenerator : public ForceGenerator
{
private:

    Vector3D m_bodyAnchor;

    Vector3D m_anchor;

    float m_k;
    float m_restingLength;

public: 

    AnchoredSpringForceGenerator(Vector3D anchor, Vector3D bodyAnchor, float k, float restingLength);
    void UpdateForce(RigidBody* rigidBody, float duration) override; 

};