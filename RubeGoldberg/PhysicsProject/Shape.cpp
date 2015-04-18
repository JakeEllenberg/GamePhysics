#include "Shape.h"


Shape::Shape()
{
}


Shape::~Shape()
{
}


std::vector<PhysicsObject*> Shape::GetPhysicsObjects()
{
	std::vector<PhysicsObject*> physicsObjects;
	for each(RenderObject* renderObject in m_Objects)
	{
		physicsObjects.push_back(renderObject);
	}
	return physicsObjects;
}