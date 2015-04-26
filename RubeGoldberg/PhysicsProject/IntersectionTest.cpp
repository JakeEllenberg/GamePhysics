//======================================================================
//File: IntersectionTest.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#include "IntersectionTest.h"


IntersectionTest::IntersectionTest()
{
}


IntersectionTest::~IntersectionTest()
{
}

//----------------------------------------------------------------------
bool IntersectionTest::BoxAndHalfSpace(const Box& box, const CollisionPlane& plane)
{
	float raidiusProjected = transformToAxis(box, plane.GetDirection());

	float boxDistance = plane.GetDirection().Dot(box.GetAxis(3)) - raidiusProjected;

	return boxDistance <= plane.GetOffset();
}

//----------------------------------------------------------------------
bool IntersectionTest::SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane)
{
	float distance = plane.GetDirection().Dot(sphere.GetAxis(3)) - sphere.GetRadius();

	return distance <= plane.GetOffset();
}

//----------------------------------------------------------------------
bool IntersectionTest::SphereAndSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo)
{
	Vector3D midLine = sphereOne.GetAxis(3) - sphereTwo.GetAxis(3);

	return midLine.MagnitudeSquared() < (sphereOne.GetRadius() + sphereTwo.GetRadius()) *
		(sphereOne.GetRadius() * sphereTwo.GetRadius());
}

//----------------------------------------------------------------------
bool IntersectionTest::BoxAndBox(const Box& boxOne, const Box& boxTwo)
{
	Vector3D toCenter = boxTwo.GetAxis(3) - boxOne.GetAxis(3);

	return (
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter) &&

		overlapOnAxis(boxOne, boxTwo, boxTwo.GetAxis(0), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxTwo.GetAxis(1), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxTwo.GetAxis(2), toCenter) &&

		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(0)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(1)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(2)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(0)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(1)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(2)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(0)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(1)), toCenter) &&
		overlapOnAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(2)), toCenter)
		);
}

//----------------------------------------------------------------------
float IntersectionTest::transformToAxis(const Box& box, const Vector3D& axis)
{
	float xAxis = box.GetHalfSize().X * abs(axis.Dot(box.GetAxis(0)));
	float yAxis = box.GetHalfSize().Y * abs(axis.Dot(box.GetAxis(1)));
	float zAxis = box.GetHalfSize().Z * abs(axis.Dot(box.GetAxis(2)));

	return xAxis + yAxis + zAxis;
}

//----------------------------------------------------------------------
bool IntersectionTest::overlapOnAxis(const Box& boxOne, const Box& boxTwo, Vector3D& axis, Vector3D& toCenter)
{
	float oneProject = transformToAxis(boxOne, axis);
	float twoProject = transformToAxis(boxTwo, axis);

	float distance = abs(toCenter.Dot(axis));

	return distance < oneProject + twoProject;
}

float IntersectionTest::penetrationOnAxis(const Box& boxOne, const Box& boxTwo, const Vector3D& axis, const Vector3D& toCenter)
{
	float projectOne = transformToAxis(boxOne, axis);
	float projectTwo = transformToAxis(boxTwo, axis);

	float distance = abs(toCenter.Dot(axis));

	return projectOne + projectTwo - distance;
}

//----------------------------------------------------------------------
bool IntersectionTest::TryAxis(const Box& boxOne, const Box& boxTwo, Vector3D axis,
	const Vector3D toCenter, unsigned int index, float& smallestPenetration, unsigned int& smallestCase)
{
	if (axis.MagnitudeSquared() < 0.0001) return true;

	float penetration = penetrationOnAxis(boxOne, boxTwo, axis, toCenter);

	if (penetration < 0)
	{
		return false;
	}
	if (penetration < smallestPenetration)
	{
		smallestPenetration = penetration;
		smallestCase = index;
	}

	return true;
}