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
Vector3D const Vector3D::Up = Vector3D(0, 1, 0);
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
Vector3D Vector3D::operator*(const Vector3D& rhs) const
{
	return Vector3D(X * rhs.X, Y * rhs.Y, Z * rhs.Z);
}
//--------------------------------------------------------------------------------
void Vector3D::operator *= (const Vector3D& rhs)
{
	X *= rhs.X;
	Y *= rhs.Y;
	Z *= rhs.Z;
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
float Vector3D::Magnitude() const
{
	return sqrt(MagnitudeSquared());
}
//--------------------------------------------------------------------------------
float Vector3D::MagnitudeSquared() const
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

//--------------------------------------------------------------------------------
void Vector3D::Lerp(Vector3D other, float rate)
{
	Vector3D difference = other - *this;
	difference = difference * rate;
	X += difference.X;
	Y += difference.Y;
	Z += difference.Z;
}

//--------------------------------------------------------------------------------
float Vector3D::GetIndex(int i)
{
	switch (i)
	{
	case 0:
		return X;
	case 1:
		return Y;
	case 2:
		return Z;
	default:
		return -1;
	}
}

//--------------------------------------------------------------------------------
void Vector3D::SetIndex(int i, float value)
{
	switch (i)
	{
	case 0:
		X = value;
	case 1:
		Y = value;
	case 2:
		Z = value;
	}
}

//--------------------------------------------------------------------------------
std::string Vector3D::ToString(bool ignoreDecimals)
{
	if (!ignoreDecimals)
	{
		return std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z);
	}
	else
	{
		//Ignores all but the first decimal
		return std::to_string(X).substr(0, std::to_string(X).size() - 5) + ", " + 
			std::to_string(Y).substr(0, std::to_string(Y).size() - 5) + ", " + 
			std::to_string(Z).substr(0, std::to_string(Z).size() - 5);
	}
}
//======================================================================