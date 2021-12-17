#include "rigidbody_contacts/CollisionDetector.h"

#include "colliders/Sphere.h"
#include "colliders/Primitive.h"

#include <vector>
#include <iostream>

void CollisionDetector::SphereAndSphere(const Sphere& one, const Sphere& two, std::vector<Contact*>* contacts)
{
	//if (data->contactLeft <= 0) return 0;

	Vector3D positionOne = one.GetCenter();
	Vector3D positionTwo = two.GetCenter();

	Vector3D midline = positionOne - positionTwo;
	float size = midline.norm();

	if (size <= 0 || size >= one.radius + two.radius) return;	//Si les objets sont trop loin on ne retourne rien

	Vector3D normal = midline / size;

	Contact* contact = new Contact(
		normal,
		positionOne - normal * one.radius,
		one.radius + two.radius - size,
		one.rb, 
		two.rb
	);

	// TODO add restitution
	// TODO add friction

	contacts->push_back(contact);
}

void CollisionDetector::BoxAndPlane(const Box& box, const Plane& plane, std::vector<Contact*>* contacts)
{
	Vector3D localCenter = Vector3D(0,0,0);

	// Get all 8 vertex in worldspace
	// Then try to find if each vertex collides with the plane
	for(int m = 0; m < 8; m++)
	{
		Vector3D v = localCenter + Vector3D(box.halfSize.x() * (m & 1 ? 1 : -1), box.halfSize.y() * (m & 2 ? 1 : -1), box.halfSize.z() * (m & 4 ? 1 : -1));
		v = box.rb->WorldPosition(v);

		Vector3D tmp = box.rb->GetRotation();

		float d = v.dot(plane.normal) + plane.distance;
		if(d <= 0)
		{
			Contact* contact = new Contact(
				plane.normal,
				v,
				-d,
				box.rb,
				nullptr
			);
			contacts->push_back(contact);
		}
	}
}

void CollisionDetector::generateContacts(const Primitive& one, const Primitive& two, std::vector<Contact*>* contacts)
{
	// SPHERE SPHERE
	if (one.GetType() == Primitive::Type::SPHERE && two.GetType() == Primitive::Type::SPHERE)
	{
		SphereAndSphere(static_cast<const Sphere&>(one), static_cast<const Sphere&>(two), contacts);
	}
	// BOX PLANE
	else if (one.GetType() == Primitive::Type::BOX && two.GetType() == Primitive::Type::PLANE)
	{
		BoxAndPlane(static_cast<const Box&>(one), static_cast<const Plane&>(two), contacts);
	}
	else if (one.GetType() == Primitive::Type::PLANE && two.GetType() == Primitive::Type::BOX)
	{
		BoxAndPlane(static_cast<const Box&>(two), static_cast<const Plane&>(one), contacts);
	}
	else
	{
		std::cerr << "Collision between " << (int)one.GetType() << " and " << (int)two.GetType() << " is not implemented yet." << std::endl;
	}
}