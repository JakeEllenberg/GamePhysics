//======================================================================
//File: Quaternion.h
//Author: Jake Ellenberg
//Created: 4/18/2015
//======================================================================
#include "Vector3D.h"
//======================================================================
#ifndef QUATERNION_H
#define QUATERNION_H
//======================================================================
class Quaternion
{
public:
	Quaternion(float r, float i, float j, float k);
	~Quaternion();

	void Normalize();
	void operator*=(const Quaternion& rhs);
	void RotateByVector(const Vector3D& vector);
	void AddScaledVector(const Vector3D& vector, float scale);
private:
	float m_R;
	float m_I;
	float m_J;
	float m_K;
};
#endif
//======================================================================