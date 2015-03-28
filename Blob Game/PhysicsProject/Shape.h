//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef SHAPE_H
#define SHAPE_H
//======================================================================
#include <vector>
#include "RenderObject.h"
#include "RodContactGenerator.h"
//======================================================================
class Shape
{
public:
	Shape();
	~Shape();

	virtual void Inititalize(Vector3D centerPosition, std::string texturePath, float length) = 0;
	std::vector<PhysicsObject*> GetPhysicsObjects();
	inline std::vector<RenderObject*> GetRenderObjects() { return m_Objects; };
	inline std::vector<RodContactGenerator*> GetRods() { return m_Rods; };

protected:
	std::vector<RenderObject*> m_Objects;
	std::vector<RodContactGenerator*> m_Rods;
};
#endif
//======================================================================