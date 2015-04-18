//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "GroundContactGenerator.h"
#include "Contact.h"
#include "CollisionSystem.h"

GroundContactGenerator::GroundContactGenerator(float groundPosition)
{
	m_GroundY = groundPosition;
}


GroundContactGenerator::~GroundContactGenerator()
{
}

void GroundContactGenerator::AddContact(CollisionSystem* collisionSystem)
{
	for each(PhysicsObject* object in collisionSystem->GetCollisionObjects())
	{
		float objectBot = object->GetPosition().Y - object->GetRadius();
		if (objectBot < m_GroundY)
		{
			float penetration = m_GroundY - objectBot;
			collisionSystem->AddContact(Contact(0.5f, Vector3D::Up, penetration,  object, nullptr));
		}
	}
}