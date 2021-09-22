#include "Particle.h"

#include <iostream>
#include <numeric>
//#include <vector>

Particle::Particle()
	: m_invMass(0), m_damping(0.001)
{ }

Particle::~Particle()
{ }

double Particle::invMass() const
{
	return m_invMass;
}

Vector3D Particle::position() const
{
	return m_position;
}

Vector3D Particle::velocity() const
{
	return m_velocity;
}

void Particle::setMass(double val)
{
	if (val == 0)
	{
		std::cerr << "[Particle::setMass] : mass can't be 0" << std::endl;
		exit(EXIT_FAILURE);
	}
	m_invMass = 1.0 / val;
}

void Particle::setInvMass(double val)
{
	m_invMass = val;
}

void Particle::Integrate(double deltaTime)
{
	// 1
	m_position += m_velocity * deltaTime + 0.5f * m_acceleration * deltaTime * deltaTime;
	// 2
	m_acceleration = m_invMass * std::accumulate(m_forces.cbegin(), m_forces.cend(), Vector3D());
	// 3
	m_velocity = m_velocity * (1 - m_damping * deltaTime) + m_acceleration * deltaTime;
}

