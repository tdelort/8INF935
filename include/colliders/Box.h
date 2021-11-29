#pragma once

#include "Primitive.h"
#include "../Vector3D.h"

class Box : public Primitive
{
public:
    Vector3D halfSize;
    // center is debug
    Vector3D center;

    inline AABB GetAABB() const override
    {
        return {center - halfSize, center + halfSize};
    }

    inline Type GetType() const override
    {
        return Type::BOX;
    }
};