#pragma once

#include "colliders/Sphere.h"
#include "colliders/Box.h"
#include "colliders/Primitive.h"

#include "../ObjMesh.h"
#include "../Cube.h"
#include "../Shader.h"
#include <glm/glm.hpp>

#include <vector>
#include <cmath>

class ContactDebugging
{
private:
	ContactDebugging() = default;
public:
	ContactDebugging(const ContactDebugging&) = delete;
	ContactDebugging& operator=(const ContactDebugging&) = delete;
	ContactDebugging(const ContactDebugging&& ) = delete;
	ContactDebugging& operator=(const ContactDebugging&& ) = delete;

	static ContactDebugging& instance()
	{
		static ContactDebugging instance;
		return instance;
	}

	Cube* cube = new Cube(createProgram(true));
	ObjMesh* sphere = new ObjMesh(createProgram(true), MeshPath::sphere);
};

struct Contact
{
	Vector3D contactNormal;
	Vector3D contactPoint;
	float interpenetration;
	RigidBody* rigidbodies[2];

	Contact(Vector3D n, Vector3D p, float i, RigidBody* rb1, RigidBody* rb2)
		: contactNormal(n), contactPoint(p), interpenetration(i), rigidbodies{ rb1, rb2 }
	{
	}
	
	void Draw()
	{

		ContactDebugging::instance().sphere->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		ContactDebugging::instance().sphere->SetScale(glm::vec3(0.1f));
		ContactDebugging::instance().sphere->SetPosition(contactPoint);

		float scale = contactNormal.norm();
		ContactDebugging::instance().cube->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
		ContactDebugging::instance().cube->SetScale(glm::vec3(scale, 0.05f, 0.05f));
		ContactDebugging::instance().cube->SetPosition(contactPoint + contactNormal * 0.5f);
		float z = std::atan2(contactNormal.y(), contactNormal.x());
		float y = std::atan2(contactNormal.z(), contactNormal.x());
		float x = 0;
		ContactDebugging::instance().cube->SetRotation(glm::vec3(x, y, z));

		ContactDebugging::instance().sphere->Draw();
		ContactDebugging::instance().cube->Draw();
	}

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