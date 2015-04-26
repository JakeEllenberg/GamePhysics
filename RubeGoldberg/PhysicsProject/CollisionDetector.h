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
#include "Box.h"
#include "IntersectionTest.h"
//======================================================================
class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	unsigned int SphereandSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionData* collisionData);
	unsigned int SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData);
	unsigned int SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData);
	unsigned int BoxAndHalfSpace(const Box& box, const CollisionPlane& plane, CollisionData* data);
	unsigned int BoxAndSphere(const Box& box, const CollisionSphere& sphere, CollisionData* data);
	unsigned int BoxAndBox(const Box& boxOne, Box& boxTwo, CollisionData* data);
private:
	Vector3D getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float oneSize,
		const Vector3D& pointTwo, const Vector3D& directionTwo, float towSize, bool useOne);
	void fillPointFaceBoxBox(const Box& boxOne, const Box& boxTwo, const Vector3D toCenter, CollisionData* data, unsigned int best, float penetration);
	static float m_Mults[8][3];
};
#endif;
//======================================================================