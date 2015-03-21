//======================================================================
//File: Contact.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef CONTACT_H
#define CONTACT_H
//======================================================================
#include "PhysicsObject.h"
//======================================================================
class Contact
{
public:
	Contact();
	Contact(float restitution, Vector3D contactNormal, float penetration, PhysicsObject* contactOne, PhysicsObject* contactTwo);
	~Contact();
	void Resolve(float deltaTime);

	
private:
	
	void resolveVelocity(float deltaTime);
	void resolveInterpenetration(float deltaTime);
	float calculateSeparatingVelocity();

	float m_Restitution;
	float m_Penetration;
	Vector3D m_ContactNormal;
	PhysicsObject* mp_ContactOne;
	PhysicsObject* mp_ContactTwo;
};
#endif
//======================================================================