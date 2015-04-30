//======================================================================
//File: RigidGroundContact.h
//Author: Jake Ellenberg
//Created: 4/27/2015
//======================================================================
#ifndef RIGID_SHAPE_CONTACT_GENERATOR_H
#define RIGID_SHAPE_CONTACT_GENERATOR_H
//======================================================================
#include "CollisionSystem.h"
#include "CollisionPlane.h"
#include "RigidContactGenerator.h"
#include "Box.h"
#include "RigidRender.h"
#include "CollisionSphere.h"
#include "RigidBox.h"
#include "RigidSphere.h"
//======================================================================
class RigidShapesContactGenerator : public RigidContactGenerator
{
public:
	RigidShapesContactGenerator();
	~RigidShapesContactGenerator();

	virtual void AddContact(CollisionSystem* collisionSystem);

private:
	std::vector<RigidBox*> GetRigidBoxes(CollisionSystem* collisionSystem);
	std::vector<RigidSphere*> GetRigidSpheres(CollisionSystem* collisionSystem);
	void BoxOnBoxContacts(std::vector<RigidBox*> boxes, CollisionSystem* collisionSystem);
	void BoxOnSphereContacts(std::vector<RigidBox*> boxes, std::vector<RigidSphere*> spheres, CollisionSystem* collisionSystem);
	void SphereOnSphereContacts(std::vector<RigidSphere*> spheres, CollisionSystem* collisionSystem);
};
#endif
//======================================================================