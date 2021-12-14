
#pragma once
#include "Contact.h"
#include "Collider.h"
#include "SphereCollider.h"


struct CollisionData{
	Contact* contacts;

	int contactsLeft;
};

class CollisionDetector {
public:


	static unsigned sphereAndSphere(const SphereCollider& one,
		const SphereCollider& two,
		CollisionData* data);