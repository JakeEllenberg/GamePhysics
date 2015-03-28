//======================================================================
//File: CableContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef CABLECONTACTGENERATOR_H
#define CABLECONTACTGENERATOR_H
//======================================================================
#include "RodContactGenerator.h"
//======================================================================
class CableContactGenerator : public RodContactGenerator
{
public:
	CableContactGenerator(PhysicsObject* endOne, PhysicsObject* endTwo, float maxLength);
	~CableContactGenerator();

	void AddContact(CollisionSystem* collisionSystem);
};
#endif
//======================================================================
