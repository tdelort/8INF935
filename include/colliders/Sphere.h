#pragma once

#include <glm/glm.hpp>
#include "Primitive.h"
#include "../Vector3D.h"

class Sphere : public Primitive
{
public:
	float radius;

	inline AABB GetAABB() const override
	{
		Vector3D center = GetCenter();
		return { center - radius, center + radius };
	}

	inline Type GetType() const override
	{
		return Type::SPHERE;
	}

	Sphere(float radius) : radius(radius) {}
};