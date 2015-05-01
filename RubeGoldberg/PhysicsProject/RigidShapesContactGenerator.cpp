#include "RigidShapesContactGenerator.h"
#include "CollisionDetector.h"


RigidShapesContactGenerator::RigidShapesContactGenerator()
{
}


RigidShapesContactGenerator::~RigidShapesContactGenerator()
{
}

void RigidShapesContactGenerator::AddContact(CollisionSystem* collisionSystem)
{
	std::vector<RigidBox*> boxes = GetRigidBoxes(collisionSystem);
	std::vector<RigidSphere*> spheres = GetRigidSpheres(collisionSystem);

	//BoxOnBoxContacts(boxes, collisionSystem);
	//BoxOnSphereContacts(boxes, spheres, collisionSystem);
	SphereOnSphereContacts(spheres, collisionSystem);
}

std::vector<RigidBox*> RigidShapesContactGenerator::GetRigidBoxes(CollisionSystem* collisionSystem)
{
	std::vector<RigidBox*> boxes;

	for each(RigidBody* body in collisionSystem->GetRigidBodies())
	{
		RigidRender* render = (RigidRender*)body;
		if (render->GetType() == RigidType::BOX)
		{
			boxes.push_back((RigidBox*)body);
		}
	}

	return boxes;
}

std::vector<RigidSphere*> RigidShapesContactGenerator::GetRigidSpheres(CollisionSystem* collisionSystem)
{
	std::vector<RigidSphere*> sphere;

	for each(RigidBody* body in collisionSystem->GetRigidBodies())
	{
		RigidRender* render = (RigidRender*)body;
		if (render->GetType() == RigidType::SPHERE)
		{
			sphere.push_back((RigidSphere*)body);
		}
	}

	return sphere;
}


void RigidShapesContactGenerator::BoxOnBoxContacts(std::vector<RigidBox*> boxes, CollisionSystem* collisionSystem)
{
	for (unsigned int i = 0; i < boxes.size(); i++)
	{
		for (unsigned int j = i + 1; j < boxes.size(); j++)
		{
			Vector3D halfsizeOne;
			halfsizeOne.X = boxes[i]->GetSize() / 2.0f;
			halfsizeOne.Y = halfsizeOne.X;
			halfsizeOne.Z = halfsizeOne.X;
			Vector3D halfsizeTwo;
			halfsizeTwo.X = boxes[j]->GetSize() / 2.0f;
			halfsizeTwo.Y = halfsizeTwo.X;
			halfsizeTwo.Z = halfsizeTwo.X;
			Box colllisionBoxOne = Box(halfsizeOne, boxes[i], Matrix());
			Box colllisionBoxTwo = Box(halfsizeTwo, boxes[j], Matrix());

			collisionSystem->GetCollisionDetector()->BoxAndBox(colllisionBoxOne, colllisionBoxTwo, collisionSystem);
		}
	}
}

void RigidShapesContactGenerator::BoxOnSphereContacts(std::vector<RigidBox*> boxes, std::vector<RigidSphere*> spheres, CollisionSystem* collisionSystem)
{
	for (unsigned int i = 0; i < boxes.size(); i++)
	{
		for (unsigned int j = 0; j < spheres.size(); j++)
		{
			Vector3D halfsizeOne;
			halfsizeOne.X = boxes[i]->GetSize() / 2.0f;
			halfsizeOne.Y = halfsizeOne.X;
			halfsizeOne.Z = halfsizeOne.X;
			Box colllisionBoxOne = Box(halfsizeOne, boxes[i], Matrix());
			CollisionSphere collisionSphereTwo = CollisionSphere(spheres[i], Matrix());
			collisionSphereTwo.SetRadius(spheres[i]->GetRadius());

			collisionSystem->GetCollisionDetector()->BoxAndSphere(colllisionBoxOne, collisionSphereTwo, collisionSystem);
		}
	}
}

void RigidShapesContactGenerator::SphereOnSphereContacts(std::vector<RigidSphere*> spheres, CollisionSystem* collisionSystem)
{
	for (unsigned int i = 0; i < spheres.size(); i++)
	{
		for (unsigned int j = i + 1; j < spheres.size(); j++)
		{
			CollisionSphere collisionSphereOne = CollisionSphere(spheres[i], Matrix());
			collisionSphereOne.SetRadius(spheres[i]->GetRadius());

			CollisionSphere collisionSphereTwo = CollisionSphere(spheres[j], Matrix());
			collisionSphereTwo.SetRadius(spheres[j]->GetRadius());

			collisionSystem->GetCollisionDetector()->SphereandSphere(collisionSphereTwo, collisionSphereOne, collisionSystem);
		}
	}
}