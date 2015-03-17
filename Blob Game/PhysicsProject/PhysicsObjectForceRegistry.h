//======================================================================
//File: PhysicsObjectForceRegistry.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Manages the registry of physics objects and force generators
//======================================================================
#ifndef PHYSICS_OBJECT_FORCE_REGISTRY_H
#define PHYSICS_OBJECT_FORCE_REGISTRY_H
//======================================================================
#include "PhysicsObject.h"
#include "ObjectForceGenerator.h"
#include "ForceGenerator.h"
#include <vector>
//======================================================================
struct ForceGeneratorRegistration
{
	PhysicsObject* m_PhysicsObject;
	ForceGenerator* m_ForceGenerator;

	//--------------------------------------------------------------------------------
	ForceGeneratorRegistration(PhysicsObject* physicsObjecct, ForceGenerator* forceGenerator)
	{
		m_PhysicsObject = physicsObjecct;
		m_ForceGenerator = forceGenerator;
	}

	//--------------------------------------------------------------------------------
	bool Equals(ForceGeneratorRegistration other)
	{
		return m_PhysicsObject == other.m_PhysicsObject && m_ForceGenerator == other.m_ForceGenerator;
	}

	//--------------------------------------------------------------------------------
	void UpdateForce()
	{
		if (m_PhysicsObject == nullptr || m_ForceGenerator == nullptr)
		{
			return;
		}

		m_ForceGenerator->UpdateForce(m_PhysicsObject);
	}
};
//======================================================================
struct ObjectForceGeneratorRegistration
{
	PhysicsObject* m_PhysicsObject1;
	PhysicsObject* m_PhysicsObject2;
	ObjectForceGenerator* m_ObjectForceGenerator;

	//--------------------------------------------------------------------------------
	ObjectForceGeneratorRegistration(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2, ObjectForceGenerator* objectForceGenerator)
	{
		m_PhysicsObject1 = physicsObject1;
		m_PhysicsObject2 = physicsObject2;
		m_ObjectForceGenerator = objectForceGenerator;
	}

	//--------------------------------------------------------------------------------
	bool Equals(ObjectForceGeneratorRegistration other)
	{
		//order does not matter
		return (m_PhysicsObject1 == other.m_PhysicsObject1 && m_PhysicsObject2 == other.m_PhysicsObject2) ||
			(m_PhysicsObject1 == other.m_PhysicsObject2 && m_PhysicsObject2 == other.m_PhysicsObject1)
			&& m_ObjectForceGenerator == other.m_ObjectForceGenerator;
	}

	//--------------------------------------------------------------------------------
	void UpdateForce()
	{
		if (m_PhysicsObject1 == nullptr || m_PhysicsObject2 == nullptr || m_ObjectForceGenerator == nullptr)
		{
			return;
		}

		m_ObjectForceGenerator->UpdateForce(m_PhysicsObject1, m_PhysicsObject2);
	}
};
//======================================================================
class PhysicsObjectForceRegistry
{
public:
	PhysicsObjectForceRegistry();
	~PhysicsObjectForceRegistry();

	void Add(PhysicsObject* physicsObject, ForceGenerator* forceGenerator);
	void Add(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2, ObjectForceGenerator* objectForceGenerator);

	void Remove(PhysicsObject* physicsObject, ForceGenerator* forceGenerator);
	void Remove(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2, ObjectForceGenerator* objectForceGenerator);

	void UpdateForces();
	void Clear();
private:
	std::vector<ForceGeneratorRegistration> m_ForceGeneratorRegistry;
	std::vector<ObjectForceGeneratorRegistration> m_ObjectForceGeneratorRegistry;
};
#endif
//======================================================================