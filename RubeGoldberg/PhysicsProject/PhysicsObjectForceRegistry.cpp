//======================================================================
//File: PhysicsObjectForceRegistry.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Manages the registry of physics objects and force generators
//======================================================================
#include "PhysicsObjectForceRegistry.h"

//======================================================================
PhysicsObjectForceRegistry::PhysicsObjectForceRegistry()
{
}

//--------------------------------------------------------------------------------
PhysicsObjectForceRegistry::~PhysicsObjectForceRegistry()
{
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Add(PhysicsObject* physicsObject, ForceGenerator* forceGenerator)
{
	m_ForceGeneratorRegistry.push_back(ForceGeneratorRegistration(physicsObject, forceGenerator));
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Add(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2, ObjectForceGenerator* objectForceGenerator)
{
	m_ObjectForceGeneratorRegistry.push_back(ObjectForceGeneratorRegistration(physicsObject1, physicsObject2, objectForceGenerator));
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Add(ForceGenerator* forceGenerator, RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo)
{
	m_RigidBodyForceRegistry.push_back(RigidbodyForceGeneratorRegistration(rigidBodyOne, rigidBodyTwo, forceGenerator));
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Remove(PhysicsObject* physicsObject, ForceGenerator* forceGenerator)
{
	ForceGeneratorRegistration searchRegistration = ForceGeneratorRegistration(physicsObject, forceGenerator);
	for (unsigned int i = 0; i < m_ForceGeneratorRegistry.size(); i++)
	{
		if (m_ForceGeneratorRegistry[i].Equals(searchRegistration))
		{
			m_ForceGeneratorRegistry.erase(m_ForceGeneratorRegistry.begin() + i);
			break;
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Remove(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2, ObjectForceGenerator* objectForceGenerator)
{
	ObjectForceGeneratorRegistration searchRegistration = ObjectForceGeneratorRegistration(physicsObject1, physicsObject2, objectForceGenerator);
	for (unsigned int i = 0; i < m_ObjectForceGeneratorRegistry.size(); i++)
	{
		if (m_ObjectForceGeneratorRegistry[i].Equals(searchRegistration))
		{
			m_ObjectForceGeneratorRegistry.erase(m_ObjectForceGeneratorRegistry.begin() + i);
			break;
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Remove(ForceGenerator* forceGenerator, RigidBody* rigidBodyOne, RigidBody* rigidBodyTwo)
{
	RigidbodyForceGeneratorRegistration searchRegistration = RigidbodyForceGeneratorRegistration(rigidBodyOne, rigidBodyTwo, forceGenerator);
	for (unsigned int i = 0; i < m_RigidBodyForceRegistry.size(); i++)
	{
		if (m_RigidBodyForceRegistry[i].Equals(searchRegistration))
		{
			m_RigidBodyForceRegistry.erase(m_RigidBodyForceRegistry.begin() + i);
			break;
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::UpdateForces()
{
	for (unsigned int i = 0; i < m_ForceGeneratorRegistry.size(); i++)
	{
		m_ForceGeneratorRegistry[i].UpdateForce();
	}
	for (unsigned int i = 0; i < m_ObjectForceGeneratorRegistry.size(); i++)
	{
		m_ObjectForceGeneratorRegistry[i].UpdateForce();
	}
	for (unsigned int i = 0; i < m_RigidBodyForceRegistry.size(); i++)
	{
		m_RigidBodyForceRegistry[i].UpdateForce();
	}

}

//--------------------------------------------------------------------------------
void PhysicsObjectForceRegistry::Clear ()
{
	m_ForceGeneratorRegistry.clear();
	m_ObjectForceGeneratorRegistry.clear();
	m_RigidBodyForceRegistry.clear();
}