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

	void Remove(PhysicsObject* physicsObject);
	void Remove(ObjectForceGenerator* objectForceGenerator);
	void Remove(ForceGenerator* forceGenerator);

	void AddToRegistry(std::vector<PhysicsObject*> objects, GeneratorType type);
	void RemoveFromRegistry(std::vector<PhysicsObject*> objects, GeneratorType type);

	void Update(float elapsedTime);
	void Reset();
	void Draw();
	void CleanUp();

private:
	std::vector<PhysicsObject*> m_PhysicsObjects;
	std::vector<ObjectForceGenerator*> m_ObjectForceGenerators;
	std::vector<ForceGenerator*> m_ForceGenerators;
	PhysicsObjectForceRegistry* mp_ForceRegistry;
};
#endif
//======================================================================