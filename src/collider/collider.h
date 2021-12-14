#pragma once

#include "../RigidBody.h"
#include "''/Matrix3x4.h"

class Collider
{
protected:
	Matrix3x4 * m_offset;
	Rigidbody* rigidbody;

public:
	
	Matrix3x4 *getOffset() const;
	Rigidbody* getRigidbody() const;