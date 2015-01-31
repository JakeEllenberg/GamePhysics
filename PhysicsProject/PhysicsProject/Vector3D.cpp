//======================================================================
//File: Vector3D.h
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Vector storage and operations
//======================================================================

#include "Vector3D.h"
#include <cmath>

//======================================================================
Vector3D const Vector3D::Zero = Vector3D(0, 0, 0);
//======================================================================
Vector3D::Vector3D()
{
	X = 0;
	Y = 0;
	Z = 0;
}

//======================================================================
Vector3D::Vector3D(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

//--------------------------------------------------------------------------------
Vector3D::~Vector3D()
{
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator*(const float& rhs) const
{
	return Vector3D(X * rhs, Y * rhs, Z * rhs);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator/(const float& rhs) const
{
	return Vector3D(X / rhs, Y / rhs, Z / rhs);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	return Vector3D(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}

//--------------------------------------------------------------------------------
float Vector3D::Dot(const Vector3D& rhs) const
{
	return X * rhs.X + Y * rhs.Y + Z * rhs.Z;
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::Cross(const Vector3D& rhs) const
{
	return Vector3D(Y * rhs.Z - Z*rhs.Y, Z * rhs.X - X * rhs.Z, X * rhs.Y - Y * rhs.X);
}

//--------------------------------------------------------------------------------
bool Vector3D::operator==(const Vector3D& rhs) const
{
	return X == rhs.X && Y == rhs.Y &&  Z == rhs.Z;
}

//--------------------------------------------------------------------------------
bool Vector3D::operator!=(const Vector3D& rhs) const
{
	return !(*this == rhs);
}

//--------------------------------------------------------------------------------
void Vector3D::operator+=(const Vector3D& rhs)
{
	X += rhs.X;
	Y += rhs.Y;
	Z += rhs.Z;
}

//--------------------------------------------------------------------------------
void Vector3D::operator-=(const Vector3D& rhs)
{
	X -= rhs.X;
	Y -= rhs.Y;
	Z -= rhs.Z;
}

//--------------------------------------------------------------------------------
float Vector3D::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
//--------------------------------------------------------------------------------
float Vector3D::MagnitudeSquared()
{
	return (X * X) + (Y * Y) + (Z * Z);
}

//--------------------------------------------------------------------------------
Vector3D Vector3D::Normalized()
{
	return *this / Magnitude();
}

//--------------------------------------------------------------------------------
void Vector3D::Normalize()
{
	Vector3D normalizedVector = Normalized();
	X = normalizedVector.X;
	Y = normalizedVector.Y;
	Z = normalizedVector.Z;
}

//--------------------------------------------------------------------------------
float Vector3D::CalculateDistanceSQ(Vector3D rhs)
{
	return pow(X - rhs.X, 2) + pow(Y - rhs.Y, 2) + pow(Z - rhs.Z, 2);
}

//--------------------------------------------------------------------------------
float Vector3D::CalculateDistance(Vector3D rhs)
{
	return sqrt(CalculateDistanceSQ(rhs));
}
//======================================================================