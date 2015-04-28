//======================================================================
//File: CollisionPrimitive.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#ifndef COLLISION_PRIMITIVE_H
#define COLLISION_PRIMITIVE_H
//======================================================================
#include "RigidBody.h"
//======================================================================
class CollisionPrimitive
{
public:
	CollisionPrimitive(RigidBody* rigidBody, Matrix offset = Matrix());
	~CollisionPrimitive();

	inline void CalculateInternals() { m_Transform = m_RigidBody->GetTransformationMatrix() * m_Offset; };

	inline Matrix GetTransform() const { return m_Transform; }

	inline Matrix GetOffset() const { return m_Offset; }

	inline Vector3D GetAxis(unsigned int index) const { return m_Transform.GetAxisVector(index); };

	inline RigidBody* GetRigidBody() const { return m_RigidBody; };

protected:
	RigidBody* m_RigidBody;
	Matrix m_Offset;
	Matrix m_Transform;
};
#endif
//======================================================================