#include "CollisionDetector.h"

unsigned CollisionDetector::sphereAndSphere(const SphereCollider& one, const SphereCollider& two, CollisionData* data)
{
	if (data->contactLeft <= 0) return 0;

	Vector3D positionOne = one.getOffset()->getAxis(3); 
	Vector3D positionTwo = two.getOffset()->getAxis(3);

	Vector3D midline = positionOne - positionTwo;
	float size = midline.norm();

	if (size <= 0 || size >= one.getRadius() + two.getRadius()) return 0;	//Si les objets sont trop loin on ne retourne rien

	Vector3D normal = midline * (1/size);

	Contact* contact = data->contact;
	contact->m_contactNormal = normal;

	contact->m_contactPoint = positionOne + midline * 0.5f;
	contact->m_penetration = (one.getRadius() + two.getRadius() - size);
	// Write the appropriate data.
	contact->m_rigidbodies[0] = one.getRigidbody();
	contact->m_rigidbodies[1] = two.getRigidbody();
	//contact->m_restitution = data->m_restitution;
	return 1;
}