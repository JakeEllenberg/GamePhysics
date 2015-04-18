//======================================================================
//File: Quaternion.h
//Author: Jake Ellenberg
//Created: 4/18/2015
//======================================================================
#ifndef QUATERNION_H
#define QUATERNION_H
//======================================================================
#include "Vector3D.h"
//======================================================================
class Quaternion
{
public:
	Quaternion();
	Quaternion(float r, float i, float j, float k);
	~Quaternion();

	void Normalize();
	void operator*=(const Quaternion& rhs);
	void RotateByVector(const Vector3D& vector);
	void AddScaledVector(const Vector3D& vector, float scale);

	float R;
	float I;
	float J;
	float K;
};
#endif
//======================================================================