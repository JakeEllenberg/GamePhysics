//======================================================================
//File: CollisionSystem.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef COLLISION_DATA_H
#define COLLISION_DATA_H
//======================================================================
#include "RigidContact.h"
//======================================================================
class CollisionData
{
public:
	CollisionData();
	~CollisionData();


	inline void AddContacts(int numContacts) { m_ContactsLeft += numContacts; };
	inline RigidContact* GetContact(){ return m_Contact; };
	inline int GetContactsLeft() { return m_ContactsLeft; };

	inline void SetFriction(float friction) { m_Friction = friction; };
	inline float GetFriction() const { return m_Friction; };

	inline void SetRestitution(float restitution) { m_Restitution = restitution; };
	inline float GetRestitution() const { return m_Restitution; };
private:
	int m_ContactsLeft;
	
	RigidContact* m_Contact;
	float m_Friction;
	float m_Restitution;
};
#endif
//======================================================================