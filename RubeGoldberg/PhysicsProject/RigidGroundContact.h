//======================================================================
//File: RigidGroundContact.h
//Author: Jake Ellenberg
//Created: 4/27/2015
//======================================================================
#ifndef RIGID_GROUND_CONTACT_H
#define RIGID_GROUND_CONTACT_H
//======================================================================
#include "CollisionSystem.h"
#include "CollisionPlane.h"
#include "RigidContactGenerator.h"
//======================================================================
class RigidGroundContact : public RigidContactGenerator
{
public:
	RigidGroundContact(float groundY);
	~RigidGroundContact();

	virtual void AddContact(CollisionSystem* collisionSystem);
private:
	CollisionPlane* m_CollisionPlane;
};
#endif
//======================================================================