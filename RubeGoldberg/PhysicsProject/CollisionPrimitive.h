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
	CollisionPrimitive();
	~CollisionPrimitive();

	inline void CalculateInternals() { m_Transform = m_RigidBody->GetTransformationMatrix() * m_Offset; };

	inline Matrix& GetTransform(){ return m_Transform; }

	inline Matrix& GetOffset(){ return m_Offset;}

	inline Vector3D GetAxis(unsigned int index) const { return m_Transform.GetAxisVector(index); };

	inline RigidBody* GetRigidBody() const { return m_RigidBody; };

protected:
	RigidBody* m_RigidBody;
	Matrix m_Offset;
	Matrix m_Transform;
};
#endif
//======================================================================