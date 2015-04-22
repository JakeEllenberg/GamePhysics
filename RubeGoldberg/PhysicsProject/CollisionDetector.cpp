//======================================================================
//File: CollisionDetector.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "CollisionDetector.h"

//======================================================================
CollisionDetector::CollisionDetector()
{
}

//======================================================================
CollisionDetector::~CollisionDetector()
{
}

//----------------------------------------------------------------------
unsigned int SphereandSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionData* collisionData)
{
	if (collisionData->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D positionOne = sphereOne.GetAxis(3);
	Vector3D positionTwo = sphereTwo.GetAxis(3);

	Vector3D midLine = positionOne - positionTwo;
	float size = midLine.Magnitude();

	if (size <= 0 || size >= sphereOne.GetRadius() + sphereTwo.GetRadius())
	{
		return 0;
	}

	Vector3D normal = midLine * 1.0f / size;
	RigidContact* contact = collisionData->GetContact();
	Vector3D contactPoint = positionOne + midLine * 0.5f;
	float pentration = sphereOne.GetRadius() + sphereTwo.GetRadius() - size;
	contact->Inititalize(collisionData->GetRestitution(), collisionData->GetFriction(), normal, contactPoint, pentration, sphereOne.GetRigidBody(), sphereTwo.GetRigidBody());
	collisionData->AddContacts(1);

	return 1;
}

//----------------------------------------------------------------------
unsigned int SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData)
{
	if (collisionData->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D position = sphere.GetAxis(3);
	
	float sphereDistance = plane.GetDirection().Dot(position) - sphere.GetRadius() - plane.GetOffset();

	RigidContact* contact = collisionData->GetContact();
	Vector3D normal = plane.GetDirection();
	Vector3D contactPoint = position - plane.GetDirection() * (sphereDistance + sphere.GetRadius());
	float pentration = -sphereDistance;
	contact->Inititalize(collisionData->GetRestitution(), collisionData->GetFriction(), normal, contactPoint, pentration, sphere.GetRigidBody(), nullptr);
	collisionData->AddContacts(1);

	return 1;
}

unsigned int SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionData* collisionData)
{
	if (collisionData->GetContactsLeft() <= 0)
	{
		return 0;
	}

	Vector3D position = sphere.GetAxis(3);

	float centerDistance = plane.GetDirection().Dot(position) - plane.GetOffset();

	if (centerDistance * centerDistance >= sphere.GetRadius() * sphere.GetRadius())
	{
		return 0;
	}

	RigidContact* contact = collisionData->GetContact();
	Vector3D normal = plane.GetDirection();
	Vector3D contactPoint = position - plane.GetDirection() * (centerDistance + sphere.GetRadius());
	float pentration = -centerDistance;
	contact->Inititalize(collisionData->GetRestitution(), collisionData->GetFriction(), normal, contactPoint, pentration, sphere.GetRigidBody(), nullptr);
	collisionData->AddContacts(1);

	return 1;
}