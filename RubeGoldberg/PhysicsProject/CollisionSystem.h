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
#include "RigidBody.h"
#include "RigidContact.h"
class CollisionDetector;
#include "RigidContactGenerator.h"
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
	void AddRigidBodies(std::vector<RigidBody*> bodies);
	void AddRigidBody(RigidBody* rigidBody);
	void AddContactGenerator(ContactGenerator* contactGenerator);
	inline void AddRigidContactGenerator(RigidContactGenerator* generator) { m_RigidContactGenerator.push_back(generator); };
	void AddRigidContact(RigidContact contact);
	void CheckCollisions();
	void AddContact(Contact& contact);
	void ResolveContacts(float deltaTime);

	

	CollisionDetector* GetCollisionDetector() { return m_CollisionDector; };

	inline int GetNumContacts(){ return (int)m_Contacts.size(); };
	inline std::vector<PhysicsObject*> GetCollisionObjects() { return m_CollisionObjects; };
	inline std::vector<RigidBody*> GetRigidBodies() { return m_RigidBodies; };
	inline float GetRestitution() { return m_Restitution; };
	inline float GetFriction() { return m_Friction; };
	inline std::vector<RigidContact> GetRigidContacts() { return m_RigidContacts; };
private:

	void resolveRigidContacts(float duration);
	void prepareRigidContacts(float duration);
	void adjustPosition(float duration);
	void adjustVelocities(float duration);

	void adjustVelocitiesLikeAParticle(float duration);
	void adjustPositionLikeAParticle(float duration);

	std::vector<PhysicsObject*> m_CollisionObjects;
	std::vector<Contact> m_Contacts;
	std::vector<ContactGenerator*> m_ContactGenerators;
	std::vector<RigidContactGenerator*> m_RigidContactGenerator;
	std::vector<RigidBody*> m_RigidBodies;
	std::vector<RigidContact> m_RigidContacts;
	CollisionDetector* m_CollisionDector;
	float m_Friction;
	float m_Restitution;
	unsigned int m_PositionIterationsUsed;
	unsigned int m_PositionIterations;
	unsigned int m_VelocityIterationsUsed;
	unsigned int m_VelocityIterations;
	float m_PositionEpsilon;
	float m_VelocityEpsilon;
};
#endif
//======================================================================