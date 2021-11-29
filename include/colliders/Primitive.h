#pragma once

#include "RigidBody.h"
#include "Matrix3x4.h"

struct AABB
{
    Vector3D min;
    Vector3D max;
};

class Primitive
{
public:
    RigidBody* rb;
    Matrix3x4 offset;

    virtual AABB GetAABB() const = 0;

    enum class Type 
    {
        BOX,
        SPHERE,
        PLANE
    };

    virtual Type GetType() const = 0;
};