//======================================================================
//File: CollisionDetector.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "CollisionDetector.h"

//======================================================================
float CollisionDetector::m_Mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 },
{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };

//======================================================================
CollisionDetector::CollisionDetector()
{
}

//======================================================================
CollisionDetector::~CollisionDetector()
{
}

//----------------------------------------------------------------------
unsigned int CollisionDetector::SphereandSphere(const CollisionSphere& sphereOne, const CollisionSphere& sphereTwo, CollisionSystem* collisionSystem)
{
	Vector3D positionOne = sphereOne.GetAxis(3);
	Vector3D positionTwo = sphereTwo.GetAxis(3);

	Vector3D midLine = positionOne - positionTwo;
	float size = midLine.Magnitude();

	if (size <= 0 || size >= sphereOne.GetRadius() + sphereTwo.GetRadius())
	{
		return 0;
	}

	Vector3D normal = midLine * 1.0f / size;
	RigidContact contact = RigidContact();
	Vector3D contactPoint = positionOne + midLine * 0.5f;
	float pentration = sphereOne.GetRadius() + sphereTwo.GetRadius() - size;
	contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), normal, contactPoint, pentration, sphereOne.GetRigidBody(), sphereTwo.GetRigidBody());

	collisionSystem->AddRigidContact(contact);

	return 1;
}

//----------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndHalfSpace(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionSystem* collisionSystem)
{

	Vector3D position = sphere.GetAxis(3);
	
	float sphereDistance = plane.GetDirection().Dot(position) - sphere.GetRadius() - plane.GetOffset();

	if (sphereDistance >= 0)
	{
		return 0;
	}

	RigidContact contact = RigidContact();
	Vector3D normal = plane.GetDirection();
	Vector3D contactPoint = position - plane.GetDirection() * (sphereDistance + sphere.GetRadius());
	float pentration = -sphereDistance;
	contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), normal, contactPoint, pentration, sphere.GetRigidBody(), nullptr);
	collisionSystem->AddRigidContact(contact);

	return 1;
}

//----------------------------------------------------------------------
unsigned int CollisionDetector::SphereAndTruePlane(const CollisionSphere& sphere, const CollisionPlane& plane, CollisionSystem* collisionSystem)
{
	Vector3D position = sphere.GetAxis(3);

	float centerDistance = plane.GetDirection().Dot(position) - plane.GetOffset();

	if (centerDistance * centerDistance >= sphere.GetRadius() * sphere.GetRadius())
	{
		return 0;
	}

	RigidContact contact = RigidContact();
	Vector3D normal = plane.GetDirection();
	Vector3D contactPoint = position - plane.GetDirection() * (centerDistance + sphere.GetRadius());
	float pentration = -centerDistance;
	contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), normal, contactPoint, pentration, sphere.GetRigidBody(), nullptr);
	collisionSystem->AddRigidContact(contact);

	return 1;
}

//----------------------------------------------------------------------
unsigned int CollisionDetector::BoxAndHalfSpace(const Box& box, const CollisionPlane& plane, CollisionSystem* collisionSystem)
{
	if (!IntersectionTest::BoxAndHalfSpace(box, plane))
	{
		return 0;
	}

	unsigned int contactsUsed = 0;
	for (unsigned int i = 0; i < 8; i++)
	{
		Vector3D vertexPos(m_Mults[i][0], m_Mults[i][1], m_Mults[i][2]);
		vertexPos *= box.GetHalfSize() * 2;
		vertexPos = box.GetTransform().Transform(vertexPos);

		float vertexDistance = vertexPos.Dot(plane.GetDirection());

		if (vertexDistance <= plane.GetOffset())
		{
			RigidContact contact;
			Vector3D contactPoint = plane.GetDirection();
			contactPoint = contactPoint * (vertexDistance - plane.GetOffset());
			contactPoint += vertexPos;
			Vector3D contactNormal = plane.GetDirection();
			float penetrationDepth = plane.GetOffset() - vertexDistance + 0.08f;
			
			contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), contactNormal, contactPoint, penetrationDepth,
				box.GetRigidBody(), NULL); 
			collisionSystem->AddRigidContact(contact);
		}
	}

	return contactsUsed;
}

//----------------------------------------------------------------------
unsigned int CollisionDetector::BoxAndSphere(const Box& box, const CollisionSphere& sphere, CollisionSystem* collisionSystem)
{
	Vector3D center = sphere.GetAxis(3);
	
	Matrix inverse = box.GetTransform().InvMatrix();
	Vector3D relCenter = inverse.Transform(center);

	bool insideX = abs(relCenter.X) - sphere.GetRadius() > box.GetHalfSize().X;
	bool insideY = abs(relCenter.Y) - sphere.GetRadius() > box.GetHalfSize().Y;
	bool insideZ = abs(relCenter.Z) - sphere.GetRadius() > box.GetHalfSize().Z;


	if ((insideX || insideY || insideZ))
	{
		return 0;
	}

	Vector3D closestPoint(0, 0, 0);
	float distance;

	distance = relCenter.X;
	if (distance > box.GetHalfSize().X)
	{
		distance = box.GetHalfSize().X;
	}
	else if (distance < -box.GetHalfSize().X)
	{
		distance = -box.GetHalfSize().X;
	}
	closestPoint.X = distance;
	distance = relCenter.Y;
	if (distance > box.GetHalfSize().Y)
	{
		distance = box.GetHalfSize().Y;
	}
	else if (distance < -box.GetHalfSize().Y)
	{
		distance = -box.GetHalfSize().Y;
	}
	closestPoint.Y = distance;
	distance = relCenter.Z;
	if (distance > box.GetHalfSize().Z)
	{
		distance = box.GetHalfSize().Z;
	}
	else if (distance < -box.GetHalfSize().Z)
	{
		distance = -box.GetHalfSize().Z;
	}
	closestPoint.Z = distance;

	distance = (closestPoint - relCenter).MagnitudeSquared();

	Vector3D closestWorldPoint = box.GetTransform().Transform(closestPoint);

	Vector3D contactNormal = closestWorldPoint - center;
	contactNormal.Normalize();
	Vector3D contactPoint = closestWorldPoint;
	float penetration = sphere.GetRadius() - sqrt(distance);

	RigidContact contact = RigidContact();
	contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), contactNormal, contactPoint,
		penetration, box.GetRigidBody(), sphere.GetRigidBody());

	collisionSystem->AddRigidContact(contact);

	return 1;
}

//----------------------------------------------------------------------
unsigned int CollisionDetector::BoxAndBox(const Box& boxOne, Box& boxTwo, CollisionSystem* collisionSystem)
{
	Vector3D toCenter = boxTwo.GetAxis(3) - boxOne.GetAxis(3);

	float penetration = FLT_MAX;

	unsigned int best = 0xffffff;

	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter, 0, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter, 1, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter, 2, penetration, best)) return 0;

	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0), toCenter, 3, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1), toCenter, 4, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2), toCenter, 5, penetration, best)) return 0;

	unsigned int bestSingleAxis = best;

	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(0)), toCenter, 6, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(1)), toCenter, 7, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(0).Cross(boxTwo.GetAxis(2)), toCenter, 8, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(0)), toCenter, 9, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(1)), toCenter, 10, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(1).Cross(boxTwo.GetAxis(2)), toCenter, 11, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(0)), toCenter, 12, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(1)), toCenter, 13, penetration, best)) return 0;
	if (!IntersectionTest::TryAxis(boxOne, boxTwo, boxOne.GetAxis(2).Cross(boxTwo.GetAxis(2)), toCenter, 14, penetration, best)) return 0;

	
	if (best == 0xffffff)
	{
		return 0;
	}

	if (best < 3)
	{
		fillPointFaceBoxBox(boxOne, boxTwo, toCenter, collisionSystem, best, penetration);
		//data->AddContacts(1);
		return 1;
	}
	else if (best < 6)
	{
		fillPointFaceBoxBox(boxTwo, boxOne, toCenter* -1.0f, collisionSystem, best - 3, penetration);
		//data->AddContacts(1);
		return 1;
	}
	else
	{
		best -= 6;
		unsigned int oneAxisIndex = best / 3;
		unsigned int twoAxisIndex = best % 3;
		Vector3D oneAxis = boxOne.GetAxis(oneAxisIndex);
		Vector3D twoAxis = boxTwo.GetAxis(twoAxisIndex);
		Vector3D axis = oneAxis.Cross(twoAxis);
		axis.Normalize();

		if (axis.Dot(toCenter) > 0)
		{
			axis = axis * -1.0f;
		}

		Vector3D pointOnEdgeOne = boxOne.GetHalfSize();
		Vector3D pointOnEdgeTwo = boxTwo.GetHalfSize();

		for (unsigned int i = 0; i < 3; i++)
		{
			if (i == oneAxisIndex) pointOnEdgeOne.SetIndex(i,0);
			else if (boxOne.GetAxis(i).Dot(axis) > 0) pointOnEdgeOne.SetIndex(i, -pointOnEdgeOne.GetIndex(i));

			if (i == twoAxisIndex) pointOnEdgeTwo.SetIndex(i, 0);
			else if (boxTwo.GetAxis(i).Dot(axis) > 0) pointOnEdgeTwo.SetIndex(i, -pointOnEdgeOne.GetIndex(i));
		}

		pointOnEdgeOne = boxOne.GetTransform() * pointOnEdgeOne;
		pointOnEdgeTwo = boxTwo.GetTransform() * pointOnEdgeTwo;

		Vector3D vertx = getContactPoint(pointOnEdgeOne, oneAxis, boxOne.GetHalfSize().GetIndex(oneAxisIndex),
			pointOnEdgeTwo, twoAxis, boxTwo.GetHalfSize().GetIndex(twoAxisIndex), bestSingleAxis > 2);

		RigidContact contact = RigidContact();

		contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), axis, vertx, penetration, boxOne.GetRigidBody(), boxTwo.GetRigidBody());
		collisionSystem->AddRigidContact(contact);
		return 1;
	}
	return 0;
}

//----------------------------------------------------------------------
void CollisionDetector::fillPointFaceBoxBox(const Box& boxOne, const Box& boxTwo, const Vector3D toCenter, CollisionSystem* collisionSystem, unsigned int best, float penetration)
{
	RigidContact contact = RigidContact();

	Vector3D normal = boxOne.GetAxis(best);
	if (boxOne.GetAxis(best).Dot(toCenter) > 0)
	{
		normal = normal * -1;
	}

	Vector3D vertex = boxTwo.GetHalfSize();
	if (boxTwo.GetAxis(0).Dot(normal) < 0)
	{
		vertex.X = -vertex.X;
	}
	if (boxTwo.GetAxis(1).Dot(normal) < 0)
	{
		vertex.Y = -vertex.Y;
	}
	if (boxTwo.GetAxis(2).Dot(normal) < 0)
	{
		vertex.Z = -vertex.Z;
	}

	Vector3D contactPoint = boxTwo.GetTransform() * vertex;

	contact.Inititalize(collisionSystem->GetRestitution(), collisionSystem->GetFriction(), normal, contactPoint, penetration,
		boxOne.GetRigidBody(), boxTwo.GetRigidBody());
	collisionSystem->AddRigidContact(contact);
}

//----------------------------------------------------------------------
Vector3D CollisionDetector::getContactPoint(const Vector3D& pointOne, const Vector3D& directionOne, float oneSize,
	const Vector3D& pointTwo, const Vector3D& directionTwo, float twoSize, bool useOne)
{
	Vector3D toSt, cOne, cTwo;
	float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	float denom, mua, mub;

	smOne = directionOne.MagnitudeSquared();
	smTwo = directionTwo.MagnitudeSquared();
	dpOneTwo = directionTwo.Dot(directionOne);

	toSt = pointOne - pointTwo;
	dpStaOne = directionOne.Dot(toSt);
	dpStaTwo = directionTwo.Dot(toSt);

	denom = smOne * smTwo - dpOneTwo * dpOneTwo;

	if (abs(denom) < 0.00001f)
	{
		return useOne ? pointOne : pointTwo;
	}

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaTwo) / denom;

	if (mua > oneSize || mua < -oneSize || mub > smTwo || mub < -twoSize)
	{
		return useOne ? pointOne : pointTwo;
	}
	else
	{
		cOne = pointOne + directionOne * mua;
		cTwo = pointTwo + directionTwo * mub;

		return cOne * 0.5 + cTwo * 0.5;
	}
}