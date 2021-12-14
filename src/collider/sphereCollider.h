
#pragma once
#include <glm/glm.hpp>
#include "Collider.h"

class SphereCollider : public Collider
{
private:
	float m_radius;

public:

	void Initialize(float radius = 1, Vector3D offset = Vector3D(0,0,0));
	
	float getRadius() const;
	void setRadius(float radius);

};