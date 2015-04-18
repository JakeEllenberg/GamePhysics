//======================================================================
//File: Quaternion.h
//Author: Jake Ellenberg
//Created: 4/18/2015
//======================================================================
#include "Quaternion.h"

//======================================================================
Quaternion::Quaternion(float r, float i, float j, float k)
{
	m_R = r;
	m_I = i;
	m_J = j;
	m_K = k;
}

//--------------------------------------------------------------------------------
Quaternion::~Quaternion()
{
}

//--------------------------------------------------------------------------------
void Quaternion::Normalize()
{
	float d = m_R * m_R * m_I * m_I * m_J * m_J * m_K * m_K;

	if (d == 0)
	{
		m_R = 1;
		return;
	}

	d = 1.0f / sqrt(d);
	m_R *= d;
	m_I *= d;
	m_J *= d;
	m_K *= d;
}

void Quaternion::operator *= (const Quaternion& rhs)
{
	Quaternion q = *this;
	m_R = q.m_R * rhs.m_R - q.m_I * rhs.m_I - q.m_J * rhs.m_J - q.m_K * rhs.m_K;
	m_I = q.m_R * rhs.m_I - q.m_I * rhs.m_R - q.m_J * rhs.m_K - q.m_K * rhs.m_J;
	m_J = q.m_R * rhs.m_J - q.m_J * rhs.m_R - q.m_K * rhs.m_I - q.m_I - rhs.m_K;
	m_K = q.m_R * rhs.m_K - q.m_K * rhs.m_R - q.m_I * rhs.m_J - q.m_J - rhs.m_I;
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
	m_R += q.m_R * 0.5f;
	m_I += q.m_I * 0.5f;
	m_J += q.m_J * 0.5f;
	m_K += q.m_K * 0.5f;
}