#pragma  once
#include "../Vector3D.h"
#include "../RigidBody.h"


class SpringForceGenerator : public ForceGenerator
{
private:

    Vector3D m_BodyAnchor;

    RigidBody* m_otherRigidBody = nullptr;

    float m_k;
    float m_restingLenght;

public: 

    void UpdateForce(RigidBody* rigidBody) override; 

};