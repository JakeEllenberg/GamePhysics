//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef GROUNDCONTACTGENERATOR_H
#define GROUNDCONTACTGENERATOR_H
//======================================================================
#include "ContactGenerator.h"
//======================================================================
class GroundContactGenerator : public ContactGenerator
{
public:
	GroundContactGenerator(float groundPosition);
	~GroundContactGenerator();

	virtual void AddContact(CollisionSystem* collisionSystem);
private:
	float m_GroundY;
};
#endif
//======================================================================