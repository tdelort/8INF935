#pragma once

#include "Primitive.h"
#include "../Vector3D.h"

class Box : public Primitive
{
public:
    Vector3D halfSize;

    inline AABB GetAABB() const override
    {
        Vector3D center = GetCenter();
        Vector3D min = center - halfSize;
        Vector3D max = center + halfSize;
		Vector3D minWorld = rb->WorldPosition(min);
        Vector3D maxWorld = rb->WorldPosition(max);

        return { minWorld, maxWorld };
    }

    inline Type GetType() const override
    {
        return Type::BOX;
    }

    Box(Vector3D halfSize) : halfSize(halfSize) {}
};