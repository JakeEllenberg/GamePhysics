#include "RigidGroundContact.h"
#include "CollisionDetector.h"
#include "RigidSphere.h"
#include "Box.h"
#include "RigidBox.h"


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
		RigidRender* rigidRenderer = (RigidRender*)collisionSystem->GetRigidBodies()[i];
		RigidType type = rigidRenderer->GetType();

		if (type == RigidType::SPHERE)
		{
			CollisionSphere sphere = CollisionSphere(collisionSystem->GetRigidBodies()[i], Matrix());
			RigidSphere* rigidSphere = (RigidSphere*)collisionSystem->GetRigidBodies()[i];
			sphere.SetRadius(rigidSphere->GetRadius());
			collisionSystem->GetCollisionDetector()->SphereAndHalfSpace(sphere, *m_CollisionPlane, collisionSystem);
		}
		else if (type == RigidType::BOX)
		{
			RigidBox* rigidBox = (RigidBox*)rigidRenderer;
			Vector3D halfsize;
			halfsize.X = rigidBox->GetSize() / 2.0f;
			halfsize.Y = halfsize.X;
			halfsize.Z = halfsize.X;
			Box colllisionBox = Box(halfsize, rigidBox, Matrix());
			collisionSystem->GetCollisionDetector()->BoxAndHalfSpace(colllisionBox, *m_CollisionPlane, collisionSystem);
		}
		
	}
}