#pragma once

#include "Primitive.h"
#include "../Vector3D.h"

class Plane : public Primitive
{
public:
    Vector3D normal;
    float distance;

    inline AABB GetAABB() const override
    {
        // TODO
        return { Vector3D(-FLT_MAX, -FLT_MAX, -FLT_MAX), Vector3D(FLT_MAX, FLT_MAX, FLT_MAX) };
    }

    inline Type GetType() const override
    {
        return Type::PLANE;
    }
};