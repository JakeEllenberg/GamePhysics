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
	for (unsigned int i = 0; i < collisionSystem->GetRigidBodies().size(); i++)
	{
		CollisionSphere sphere = CollisionSphere(collisionSystem->GetRigidBodies()[i], Matrix());
		RigidSphere* rigidSphere = (RigidSphere*)collisionSystem->GetRigidBodies()[i];
		sphere.SetRadius(rigidSphere->GetRadius());
		collisionSystem->GetCollisionDetector()->SphereAndHalfSpace(sphere, *m_CollisionPlane, collisionSystem);
	}
}