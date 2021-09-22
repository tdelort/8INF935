#pragma once

#include <iostream>

class Vector3D
{
private:
	double m_x, m_y, m_z;

public:
	Vector3D(); //constructor
	Vector3D(double x, double y, double z); //constructor
	~Vector3D(); //destructor

	double x() const;
	double y() const;
	double z() const;

	void setX(double val);
	void setY(double val);
	void setZ(double val);
	
	// TODO create a static counterpart
	static double norm(const Vector3D& v);
	static Vector3D normalize(const Vector3D& v);
	static double dot(const Vector3D& lhs, const Vector3D& rhs);
	static Vector3D cross(const Vector3D& lhs, const Vector3D& rhs);

	double norm() const;
	Vector3D normalize() const;
	double dot(const Vector3D& other) const;
	Vector3D cross(const Vector3D& other) const;
	
	Vector3D operator-();
	Vector3D& operator+=(const Vector3D& rhs);
	Vector3D& operator-=(const Vector3D& rhs);

	Vector3D& operator+=(double rhs);
	Vector3D& operator-=(double rhs);
	Vector3D& operator*=(double rhs);
	Vector3D& operator/=(double rhs);
	
	Vector3D operator+(const Vector3D& rhs);
	Vector3D operator-(const Vector3D& rhs);
	Vector3D operator+(double rhs);
	Vector3D operator-(double rhs);

	Vector3D operator*(double rhs);
	Vector3D operator/(double rhs);

	bool operator==(const Vector3D& other);
	bool operator!=(const Vector3D& other);

	friend Vector3D operator*(double lhs, const Vector3D& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const Vector3D& v);
};

