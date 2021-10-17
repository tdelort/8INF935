#include "Vector3D.h"

#include <iostream>
#include <cmath>

Vector3D::Vector3D() 
	: m_x(0), m_y(0), m_z(0)
{ }

Vector3D::Vector3D(double x, double y, double z)
	: m_x(x), m_y(y), m_z(z)
{ }

//TODO : change when needed
// There is no ressources allocated so the destructor can be left empty
Vector3D::~Vector3D()
{ }

// Setters and Getters
double Vector3D::x() const
{ return m_x; }

double Vector3D::y() const
{ return m_y; }

double Vector3D::z() const
{ return m_z; }

void Vector3D::setX(double val)
{ m_x = val; }

void Vector3D::setY(double val)
{ m_y = val; }

void Vector3D::setZ(double val)
{ m_z = val; }

//static methods
double Vector3D::norm(const Vector3D& v)
{
	return v.norm();
}

Vector3D Vector3D::normalize(const Vector3D& v)
{	
	return v.normalize();
}

double Vector3D::dot(const Vector3D& lhs, const Vector3D& rhs)
{
	return lhs.dot(rhs);
}

Vector3D Vector3D::cross(const Vector3D& lhs, const Vector3D& rhs)
{
	return lhs.cross(rhs);
}

//methods
double Vector3D::norm() const
{
	return std::sqrt(this->dot(*this));
}

Vector3D Vector3D::normalize() const
{	
	Vector3D result(*this);
	result /= result.norm();
	return result;
}

double Vector3D::dot(const Vector3D& other) const
{
	return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

Vector3D Vector3D::cross(const Vector3D& other) const
{
	double x = m_y * other.m_z - m_z * other.m_y;
	double y = m_z * other.m_x - m_x * other.m_z;
	double z = m_x * other.m_y - m_y * other.m_x;
	return Vector3D(x, y, z);
}



Vector3D Vector3D::operator-() const
{
	return Vector3D(-m_x, -m_y, -m_z);
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	m_z += rhs.m_z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	m_z -= rhs.m_z;
	return *this;
}

Vector3D& Vector3D::operator+=(double rhs)
{
	m_x += rhs;
	m_y += rhs;
	m_z += rhs;
	return *this;
}

Vector3D& Vector3D::operator-=(double rhs)
{
	m_x -= rhs;
	m_y -= rhs;
	m_z -= rhs;
	return *this;
}

Vector3D& Vector3D::operator*=(double rhs)
{
	m_x *= rhs;
	m_y *= rhs;
	m_z *= rhs;
	return *this;
}

Vector3D& Vector3D::operator/=(double rhs)
{
	return *this *= (1.0 / rhs);
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(*this) += rhs;
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D(*this) -= rhs;
}


Vector3D Vector3D::operator+(double rhs) const
{
	return Vector3D(*this) += rhs;
}

Vector3D Vector3D::operator-(double rhs) const
{
	return Vector3D(*this) -= rhs;
}

Vector3D Vector3D::operator*(double rhs) const
{
	return Vector3D(*this) *= rhs;
}

Vector3D Vector3D::operator/(double rhs) const
{
	if (rhs == 0)
	{ 
		std::cerr << "[Vector3D::operator/] : Division by 0 is not allowed" << std::endl;
		exit(EXIT_FAILURE);
	}
	return Vector3D(*this) /= rhs;
}

bool Vector3D::operator==(const Vector3D& other) const
{
	return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

bool Vector3D::operator!=(const Vector3D& other) const
{
	return !(*this == other);
}



// Friend functions
std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
	os << "[" << v.m_x << "; " << v.m_y << "; " << v.m_z << "]";
	return os;
}

Vector3D operator*(double lhs, const Vector3D& rhs)
{
	return Vector3D(rhs) *= lhs;
}

