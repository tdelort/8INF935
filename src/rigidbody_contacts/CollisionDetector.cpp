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

	Vector3D normal = midline * (1/size);

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

void CollisionDetector::generateContacts(const Primitive& one, const Primitive& two, std::vector<Contact*>* contacts)
{
	if (one.GetType() == Primitive::Type::SPHERE && two.GetType() == Primitive::Type::SPHERE)
	{
		SphereAndSphere(
			static_cast<const Sphere&>(one),
			static_cast<const Sphere&>(two),
			contacts
		);
	}
	else
	{
		std::cerr << "Collision between " << (int)one.GetType() << " and " << (int)two.GetType() << " is not implemented yet." << std::endl;
	}
}