//======================================================================
//File: RigidBody.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#ifndef COLLISION_PLANE_H
#define COLLISION_PLANE_H
//======================================================================
#include "Vector3D.h"
//======================================================================
class CollisionPlane
{
public:
	CollisionPlane();
	~CollisionPlane();

	inline Vector3D GetDirection() const { return m_Direction; };
	inline void SetDirection(Vector3D direction) { m_Direction = direction; };
	inline float GetOffset() const { return m_Offset; };
	inline void SetOffset(float offset) { m_Offset = offset; };

private:
	Vector3D m_Direction;
	float m_Offset;
};
#endif
//======================================================================