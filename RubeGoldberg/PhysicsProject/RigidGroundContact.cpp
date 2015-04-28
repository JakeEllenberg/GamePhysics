#include "RigidGroundContact.h"
#include "CollisionDetector.h"
#include "RigidSphere.h"


RigidGroundContact::RigidGroundContact(float groundY)
{
	m_CollisionPlane = new CollisionPlane();
	m_CollisionPlane->SetDirection(Vector3D(0, 1, 0));
	m_CollisionPlane->SetOffset(groundY);
}


RigidGroundContact::~RigidGroundContact()
{
	delete m_CollisionPlane;
}

void RigidGroundContact::AddContact(CollisionSystem* collisionSystem)
{
	for each(RigidBody* body in collisionSystem->GetRigidBodies())
	{
		CollisionSphere sphere = CollisionSphere(body, Matrix());
		RigidSphere* rigidSphere = (RigidSphere*)body;
		sphere.SetRadius(rigidSphere->GetRadius());
		collisionSystem->GetCollisionDetector()->SphereAndHalfSpace(sphere, *m_CollisionPlane, collisionSystem);
	}
}