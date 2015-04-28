//======================================================================
//File: CollisionDetector.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#ifndef COLLISION_SPHERE_H
#define COLLISION_SPHERE_H
//======================================================================
#include "CollisionPrimitive.h"
//======================================================================
class CollisionSphere : public CollisionPrimitive
{
public:
	CollisionSphere(RigidBody* rigidBody, Matrix offset);
	~CollisionSphere();

	inline void SetRadius(float radius) { m_Radius = radius; };
	inline float GetRadius() const { return m_Radius; };

private:
	float m_Radius;
};
#endif
//======================================================================