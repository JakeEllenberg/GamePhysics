//======================================================================
//File: RigidBodySpringContactGenerator.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef RIGID_BODY_SPRING_FORCE_GENERATOR_H
#define RIGID_BODY_SPRING_FORCE_GENERATOR_H
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class RigidBodySpringForceGenerator :
	public ForceGenerator
{
public:
	RigidBodySpringForceGenerator(const Vector3D& localConnectionPoint, RigidBody* anchorObject, const Vector3D &otherConnectionPoint, float springConstant, float restLength);
	~RigidBodySpringForceGenerator();

	virtual void UpdateForce(RigidBody* rigidbodyOne, RigidBody* rigidbodyTwo = NULL);
private:
	Vector3D m_ConnectionPoint;
	Vector3D m_OtherConnectionPoint;

	RigidBody* m_AnchorRigidBody;

	float m_SpringConstant;
	float m_RestLength;
};
#endif
//======================================================================