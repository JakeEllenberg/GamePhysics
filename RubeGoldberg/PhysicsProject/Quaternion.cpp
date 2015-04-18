//======================================================================
//File: Quaternion.h
//Author: Jake Ellenberg
//Created: 4/18/2015
//======================================================================
#include "Quaternion.h"

//======================================================================
Quaternion::Quaternion()
{
	R = 1;
	I = 0;
	J = 0;
	K = 0;
}

//--------------------------------------------------------------------------------
Quaternion::Quaternion(float r, float i, float j, float k)
{
	R = r;
	I = i;
	J = j;
	K = k;
}

//--------------------------------------------------------------------------------
Quaternion::~Quaternion()
{
}

//--------------------------------------------------------------------------------
void Quaternion::Normalize()
{
	float d = R * R * I * I * J * J * K * K;

	if (d == 0)
	{
		R = 1;
		return;
	}

	d = 1.0f / sqrt(d);
	R *= d;
	I *= d;
	J *= d;
	K *= d;
}

void Quaternion::operator *= (const Quaternion& rhs)
{
	Quaternion q = *this;
	R = q.R * rhs.R - q.I * rhs.I - q.J * rhs.J - q.K * rhs.K;
	I = q.R * rhs.I - q.I * rhs.R - q.J * rhs.K - q.K * rhs.J;
	J = q.R * rhs.J - q.J * rhs.R - q.K * rhs.I - q.I - rhs.K;
	K = q.R * rhs.K - q.K * rhs.R - q.I * rhs.J - q.J - rhs.I;
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
	Quaternion q(0, vector.X, vector.Y, vector.Z);
	(*this) *= q;
}

void Quaternion::AddScaledVector(const Vector3D& vector, float scale)
{
	Vector3D scaledVector = vector * scale;
	Quaternion q(0, scaledVector.X, scaledVector.Y, scaledVector.Z);
	q *= *this;
	R += q.R * 0.5f;
	I += q.I * 0.5f;
	J += q.J * 0.5f;
	K += q.K * 0.5f;
}