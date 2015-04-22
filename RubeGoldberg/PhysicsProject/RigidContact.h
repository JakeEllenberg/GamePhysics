//======================================================================
//File: RigidContact.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#ifndef RIGIDCONTACT_H
#define RIGIDCONTACT_H
//======================================================================
#include "Vector3D.h"
#include "RigidBody.h"
//======================================================================
class RigidContact
{
public:
	RigidContact();
	~RigidContact();

	void Inititalize(float Restitution, float Friction, Vector3D contactNormal, Vector3D contactPoint, float pentration, RigidBody* bodyOne, RigidBody* bodyTwo = nullptr);

private:
	float m_Restitution;
	float m_Friction;
	float m_Pentration;
	Vector3D m_ContactNormal;
	Vector3D m_ContactPoint;
	
	RigidBody* m_BodyOne;
	RigidBody* m_BodyTwo;
};
#endif
//======================================================================