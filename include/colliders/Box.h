#pragma once

#include "Primitive.h"
#include "../Vector3D.h"

class Box : public Primitive
{
public:
    Vector3D halfSize;

    inline AABB GetAABB() const override
    {
		Vector3D center = rb->WorldPosition(offset.GetPosition());
        return {center - halfSize, center + halfSize};
    }

    inline Type GetType() const override
    {
        return Type::BOX;
    }
};