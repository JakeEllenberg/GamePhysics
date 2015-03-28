//======================================================================
//File: CableContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "CableContactGenerator.h"
#include "CollisionSystem.h"

CableContactGenerator::CableContactGenerator(PhysicsObject* endOne, PhysicsObject* endTwo, float maxLength)
:RodContactGenerator(endOne, endTwo, maxLength)
{
}


CableContactGenerator::~CableContactGenerator()
{
}

//-----------------------------------------------------------------------------
void CableContactGenerator::AddContact(CollisionSystem* collisionSystem)
{
	float length = currentLength();
	if (length <= m_MaxLength) return;

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