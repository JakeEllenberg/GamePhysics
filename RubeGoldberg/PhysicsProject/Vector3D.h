//======================================================================
//File: Vector3D.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Vector storage and operations
//======================================================================
#include <string>
//======================================================================
#ifndef VECTOR3D_H
#define VECTOR3D_H
class Vector3D
{
public:
	float X;
	float Y;
	float Z;
	static const Vector3D Zero;
	static const Vector3D Up;

	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	
	Vector3D operator*(const Vector3D& rhs) const;
	void operator*=(const Vector3D& rhs);
	Vector3D operator*(const float&) const;
	Vector3D operator/(const float&) const;
	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	bool operator==(const Vector3D&) const;
	bool operator!=(const Vector3D&) const;

	void operator+=(const Vector3D&);
	void operator-=(const Vector3D&);

	float Dot(const Vector3D&) const;
	Vector3D Cross(const Vector3D&) const;
	float Magnitude() const ;
	float MagnitudeSquared() const;

	void Normalize();
	Vector3D Normalized();

	float CalculateDistanceSQ(Vector3D rhs);
	float CalculateDistance(Vector3D rhs);

	void Lerp(Vector3D other, float rate);

	float GetIndex(int i);
	void SetIndex(int i, float value);

	std::string ToString(bool ignoreDecimals = false);
};
#endif
//======================================================================
