//======================================================================
//File: ContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef CONTACTGENERATOR_H
#define CONTACTGENERATOR_H
//======================================================================
#include "Contact.h"
class CollisionSystem;
//======================================================================
class ContactGenerator
{
public:
	ContactGenerator();
	~ContactGenerator();

	virtual void AddContact(CollisionSystem* collisionSystem) = 0;
};
#endif
//======================================================================