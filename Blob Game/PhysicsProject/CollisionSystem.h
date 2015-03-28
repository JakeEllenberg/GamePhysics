//======================================================================
//File: CollisionSystem.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
//======================================================================
#include "Ground.h"
#include <vector>
#include "PhysicsObject.h"
#include "Contact.h"
#include "GroundContactGenerator.h"
#include "ContactGenerator.h"
//======================================================================

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void CleanUp();
	void Inititalize(float groundPos);
	void AddCollisionObjects(std::vector<PhysicsObject*> objects);
	void AddCollisionObject(PhysicsObject* object);
	void AddContactGenerator(ContactGenerator* contactGenerator);
	void CheckCollisions();
	void AddContact(Contact& contact);
	void ResolveContacts(float deltaTime);

	inline int GetNumContacts(){ return (int)m_Contacts.size(); };
	inline std::vector<PhysicsObject*> GetCollisionObjects() { return m_CollisionObjects; };

private:
	std::vector<PhysicsObject*> m_CollisionObjects;
	std::vector<Contact> m_Contacts;
	std::vector<ContactGenerator*> m_ContactGenerators;
};
#endif
//======================================================================