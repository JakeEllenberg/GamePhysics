//======================================================================
//File: RodContactGenerator.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef ROD_CONTACT_GENERATOR_H
#define ROD_CONTACT_GENERATOR_H
//======================================================================
#include "RodContactGenerator.h"
#include "CollisionSystem.h"
#include <math.h>
//======================================================================
//-----------------------------------------------------------------------------
RodContactGenerator::RodContactGenerator(PhysicsObject* endOne, PhysicsObject* endTwo, float maxLength)
{
	m_EndOne = endOne;
	m_EndTwo = endTwo;
	m_MaxLength = maxLength;
}

//-----------------------------------------------------------------------------
RodContactGenerator::~RodContactGenerator()
{
}

//-----------------------------------------------------------------------------
float RodContactGenerator::currentLength()
{
	return m_EndOne->GetPosition().CalculateDistance(m_EndTwo->GetPosition());
}

//-----------------------------------------------------------------------------
void RodContactGenerator::AddContact(CollisionSystem* collisionSystem)
{
	float length = currentLength();
	if (length == m_MaxLength) return;

	Vector3D normal = m_EndTwo->GetPosition() - m_EndOne->GetPosition();
	normal.Normalize();
	float penetration = 0.0f;
	float restitution = 0.0f;

	if (length > m_MaxLength) 
	{
		penetration = length - m_MaxLength;
	}
	else 
	{
		normal = normal * -1.0f;
		penetration = m_MaxLength - length;
	}

	collisionSystem->AddContact(Contact(restitution, normal, penetration, m_EndOne, m_EndTwo));
}
#endif
//======================================================================