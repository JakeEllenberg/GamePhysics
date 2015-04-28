//======================================================================
//File: BOX.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#ifndef BOX_H
#define BOX_H
//======================================================================
#include "CollisionPrimitive.h"
//======================================================================

class Box : public CollisionPrimitive
{
public:
	Box(Vector3D halfSize, RigidBody* rigidBody, Matrix offset);
	~Box();

	inline Vector3D GetHalfSize() const { return m_HalfSize; };
private:
	Vector3D m_HalfSize;
	Vector3D m_Vertices[8];
};
#endif