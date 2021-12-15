#pragma once

#include "colliders/Sphere.h"
#include "colliders/Box.h"
#include "colliders/Primitive.h"

#include <vector>

struct Contact
{
	Vector3D contactNormal;
	Vector3D contactPoint;
	float interpenetration;
	RigidBody* rigidbodies[2];

	Contact(Vector3D n, Vector3D p, float i, RigidBody* rb1, RigidBody* rb2)
		: contactNormal(n), contactPoint(p), interpenetration(i), rigidbodies{ rb1, rb2 }
	{ }
};

class CollisionDetector 
{
	static void SphereAndSphere(
		const Sphere& one,
		const Sphere& two,
		std::vector<Contact*>* contacts
	);

	public:

	static void generateContacts(
		const Primitive& one,
		const Primitive& two,
		std::vector<Contact*>* contacts
	);

};