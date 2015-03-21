//======================================================================
//File: RodContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef RODCONTACTGENERATOR_H
#define RODCONTACTGENERATOR_H
//======================================================================
#include "ContactGenerator.h"
//======================================================================
class RodContactGenerator : public ContactGenerator
{
public:
	RodContactGenerator(PhysicsObject* endOne, PhysicsObject* endTwo, float maxLength);
	~RodContactGenerator();

	void AddContact(CollisionSystem* collisionSystem);
private:
	float currentLength();

	float m_MaxLength;
	PhysicsObject* m_EndOne;
	PhysicsObject* m_EndTwo;
};
#endif
//======================================================================