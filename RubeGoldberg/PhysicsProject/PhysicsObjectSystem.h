//======================================================================
//File: PhysicsObjectSystem.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Manages the physics objects
//======================================================================
#ifndef PHYSICSOBJECTSYSTEM_H
#define PHYSICSOBJECTSYSTEM_H
//======================================================================
#include "PhysicsObject.h"
#include "ObjectForceGenerator.h"
#include "ForceGenerator.h"
#include "PhysicsObjectForceRegistry.h"
#include <vector>
#include "Generator.h"
#include "CollisionSystem.h"
//======================================================================
class PhysicsObjectSystem
{
public:
	PhysicsObjectSystem();
	~PhysicsObjectSystem();

	void Initialize();

	void Add(PhysicsObject* physicsObject);
	void Add(ObjectForceGenerator* objectForceGenerator);
	void Add(ForceGenerator* forceGenerator);
	void Add(ContactGenerator* contactGenerator);
	void Add(RigidContactGenerator* contactGenerator);
	void Add(RigidBody* rigidBody);

	void Remove(PhysicsObject* physicsObject);
	void Remove(ObjectForceGenerator* objectForceGenerator);
	void Remove(ForceGenerator* forceGenerator);

	void AddToRegistry(PhysicsObject* object, ForceGenerator* generator);
	void AddToRegistry(ForceGenerator* generator, RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo = NULL);
	void AddToRegistry(std::vector<PhysicsObject*> objects, GeneratorType type);
	void RemoveFromRegistry(std::vector<PhysicsObject*> objects, GeneratorType type);

	void Update(float elapsedTime);
	
	void Reset();
	void CleanUp();

private:
	void updateComponent(float elapsedTime);
	void updateCollisions(float elapsedTime);

	std::vector<PhysicsObject*> m_PhysicsObjects;
	std::vector<ObjectForceGenerator*> m_ObjectForceGenerators;
	std::vector<ForceGenerator*> m_ForceGenerators;
	std::vector<RigidBody*> m_RigidBodys;
	PhysicsObjectForceRegistry* mp_ForceRegistry;
	CollisionSystem* mp_CollisionSystem;
};
#endif
//======================================================================