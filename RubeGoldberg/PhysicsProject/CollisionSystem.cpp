//======================================================================
//File: CollisionSystem.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "CollisionSystem.h"

//--------------------------------------------------------------------------------
CollisionSystem::CollisionSystem()
{
}

//--------------------------------------------------------------------------------
CollisionSystem::~CollisionSystem()
{
}

//--------------------------------------------------------------------------------
void CollisionSystem::Inititalize(float groundPos)
{
	m_ContactGenerators.push_back(new GroundContactGenerator(groundPos));
}

//--------------------------------------------------------------------------------
void CollisionSystem::AddCollisionObjects(std::vector<PhysicsObject*> objects)
{
	for each(PhysicsObject* object in objects)
	{
		m_CollisionObjects.push_back(object);
	}
}

//--------------------------------------------------------------------------------
void CollisionSystem::AddCollisionObject(PhysicsObject* object)
{
	m_CollisionObjects.push_back(object);
}

void CollisionSystem::AddContactGenerator(ContactGenerator* contact)
{
	m_ContactGenerators.push_back(contact);
}

//--------------------------------------------------------------------------------
void CollisionSystem::AddContact(Contact& contact)
{
	m_Contacts.push_back(contact);
}

//--------------------------------------------------------------------------------
void CollisionSystem::ResolveContacts(float deltaTime)
{
	for each(Contact contact in m_Contacts)
	{
		contact.Resolve(deltaTime);
	}
	m_Contacts.clear();
}

//--------------------------------------------------------------------------------
void CollisionSystem::CheckCollisions()
{
	for each(ContactGenerator* contactGenerator in m_ContactGenerators)
	{
		contactGenerator->AddContact(this);
	}
}

void CollisionSystem::CleanUp()
{
	for each(ContactGenerator* contactGenerator in m_ContactGenerators)
	{
		delete contactGenerator;
	}
	m_ContactGenerators.clear();
}