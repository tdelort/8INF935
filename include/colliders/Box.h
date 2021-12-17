#pragma once

#include "Primitive.h"
#include "../Vector3D.h"

class Box : public Primitive
{
public:
    Vector3D halfSize;

    inline AABB GetAABB() const override
    {
        Vector3D min = GetCenter();
        Vector3D max = min;
        Vector3D localCenter = offset.GetPosition();
        for(int m = 0; m < 8; m++)
        {
            Vector3D v = localCenter + Vector3D(halfSize.x() * (m & 1 ? 1 : -1), halfSize.y() * (m & 2 ? 1 : -1), halfSize.z() * (m & 4 ? 1 : -1));
            v = rb->WorldPosition(v);
            min.setX(std::min(min.x(), v.x()));
            min.setY(std::min(min.y(), v.y()));
            min.setZ(std::min(min.z(), v.z()));
            max.setX(std::max(max.x(), v.x()));
            max.setY(std::max(max.y(), v.y()));
            max.setZ(std::max(max.z(), v.z()));
        }

        return { min, max };
    }

    inline Type GetType() const override
    {
        return Type::BOX;
    }

    Box(Vector3D halfSize) : halfSize(halfSize) {}
};