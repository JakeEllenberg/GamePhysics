//======================================================================
//File: IntersectionTest.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#ifndef INTERSECTION_TEST_H
#define INTERSECTION_TEST_H
//======================================================================
#include "Box.h"
#include "CollisionPlane.h"
#include "Vector3D.h"
#include "CollisionSphere.h"
//======================================================================
class IntersectionTest
{
public:
	IntersectionTest();
	~IntersectionTest();
	static bool BoxAndHalfSpace(const Box& box, const CollisionPlane& plane);
	static bool SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane);
	static bool SphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo);
	static bool BoxAndBox(const Box& boxOne, const Box& boxTwo);
	static bool TryAxis(const Box& boxOne, const Box& boxTwo, Vector3D axis,
		const Vector3D toCenter, unsigned int index, float& smallestPenetration,unsigned int& smallestCase);



private:
	static float penetrationOnAxis(const Box& boxOne, const Box& boxTwo, const Vector3D& axis, const Vector3D& toCenter);
	static float transformToAxis(const Box& box, const Vector3D& axis);
	static bool overlapOnAxis(const Box& boxOne, const Box& boxTwo, Vector3D& axis, Vector3D& toCenter);
};
#endif
//======================================================================