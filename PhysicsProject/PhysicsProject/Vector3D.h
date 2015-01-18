//======================================================================
//File: Vector3D.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Vector storage and operations
//======================================================================
#ifndef VECTOR3D_H
#define VECTOR3D_H
class Vector3D
{
public:
	float X;
	float Y;
	float Z;

	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();

	Vector3D operator*(const float&) const;
	Vector3D operator/(const float&) const;
	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	bool operator==(const Vector3D&) const;
	bool operator!=(const Vector3D&) const;

	float Dot(const Vector3D&) const;
	Vector3D Cross(const Vector3D&) const;
	float Magnitued();
	float MagnitudeSquared();

	void Normalize();
	Vector3D Normalized();
};
#endif
//======================================================================
