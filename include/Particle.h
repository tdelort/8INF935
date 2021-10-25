#pragma once

#include "Vector3D.h"
#include "IIntegrable.h"

#include <vector>

class Particle : public IIntegrable
{
private:
	Vector3D m_position;
	Vector3D m_velocity;
	Vector3D m_acceleration;
	std::vector<Vector3D> m_forces;

	double m_invMass;
	double m_damping;

public:
	Particle();
	~Particle();

	double invMass() const;
	Vector3D position() const;
	Vector3D velocity() const;
	std::vector<Vector3D> forces() const;

	void setPosition(const Vector3D& pos);
	void setVelocity(const Vector3D& vel);
	void addForce(const Vector3D& force);
	void clearForces();

	void setMass(double val);
	void setInvMass(double val);
	
	void Integrate(double deltaTime) override;
};
