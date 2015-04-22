//======================================================================
//File: CollisionDetector.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef COLLISION_DECTOR_H
#define COLLISION_DECTOR_H
//======================================================================
#include "RigidContact.h"
#include "CollisionSphere.h"
#include "CollisionData.h"
#include "CollisionPlane.h"
//======================================================================
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	unsigned int SphereandSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionData* collisionData);
	unsigned int SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData);
	unsigned int SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData);

};
#endif;
//======================================================================