//======================================================================
//File: CollisionPrimitive.cpp
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#include "CollisionPrimitive.h"

//======================================================================
CollisionPrimitive::CollisionPrimitive(RigidBody* rigidBody, Matrix offset)
{
	m_Offset = offset;
	m_RigidBody = rigidBody;

	CalculateInternals();
}


CollisionPrimitive::~CollisionPrimitive()
{
}
