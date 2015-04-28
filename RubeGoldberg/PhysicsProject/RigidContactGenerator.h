//======================================================================
//File: ContactGenerator.h
//Author: Jake Ellenberg
//Created: 4/27/2015
//======================================================================
#ifndef RIGID_CONTACT_GENERATOR_H
#define RIGID_CONTACT_GENERATOR_H
//======================================================================
class CollisionSystem;
//======================================================================
class RigidContactGenerator
{
public:
	RigidContactGenerator();
	~RigidContactGenerator();

	virtual void AddContact(CollisionSystem* collisionSystem) = 0;
};
#endif
//======================================================================