//======================================================================
//File: PhysicsObjectSystem.cpp
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Manages the physics objects
//======================================================================
#include "PhysicsObjectSystem.h"

//======================================================================
PhysicsObjectSystem::PhysicsObjectSystem()
{
}

//--------------------------------------------------------------------------------
PhysicsObjectSystem::~PhysicsObjectSystem()
{
	CleanUp();
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Initialize()
{
	mp_ForceRegistry = new PhysicsObjectForceRegistry();
	mp_CollisionSystem = new CollisionSystem();
	mp_CollisionSystem->Inititalize(0.0f);
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Add(PhysicsObject* physicsObject)
{
	m_PhysicsObjects.push_back(physicsObject);
	mp_CollisionSystem->AddCollisionObject(physicsObject);
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Add(ObjectForceGenerator* objectForceGenerator)
{
	m_ObjectForceGenerators.push_back(objectForceGenerator);
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Add(ForceGenerator* forceGenerator)
{
	m_ForceGenerators.push_back(forceGenerator);
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Add(ContactGenerator* contactGenerator)
{
	mp_CollisionSystem->AddContactGenerator(contactGenerator);
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Remove(PhysicsObject* physicsObject)
{
	for (unsigned int i = 0; i < m_PhysicsObjects.size(); i++)
	{
		if (physicsObject == m_PhysicsObjects[i])
		{
			delete physicsObject;
			m_PhysicsObjects.erase(m_PhysicsObjects.begin() + i);
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Remove(ObjectForceGenerator* objectForceGenerator)
{
	for (unsigned int i = 0; i < m_ObjectForceGenerators.size(); i++)
	{
		if (objectForceGenerator == m_ObjectForceGenerators[i])
		{
			delete objectForceGenerator;
			m_ObjectForceGenerators.erase(m_ObjectForceGenerators.begin() + i);
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Remove(ForceGenerator* forceGenerator)
{
	for (unsigned int i = 0; i < m_ForceGenerators.size(); i++)
	{
		if (forceGenerator == m_ForceGenerators[i])
		{
			delete forceGenerator;
			m_ForceGenerators.erase(m_ForceGenerators.begin() + i);
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::AddToRegistry(std::vector<PhysicsObject*> objects, GeneratorType type)
{
	bool twoObjects = type >= GeneratorType::OBJECT_FORCE_GENERATOR;

	if (!twoObjects)
	{
		ForceGenerator* currentGenerator = nullptr;
		for (unsigned int i = 0; i < m_ForceGenerators.size(); i++)
		{
			if (m_ForceGenerators[i]->GetType() == type)
			{
				currentGenerator = m_ForceGenerators[i];
				break;
			}
		}

		//Check to see if the desired generator exist
		if (currentGenerator == nullptr)
		{
			return;
		}

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			mp_ForceRegistry->Add(objects[i], currentGenerator);
		}
	}
	else
	{
		ObjectForceGenerator* currentGenerator = nullptr;
		for (unsigned int i = 0; i < m_ObjectForceGenerators.size(); i++)
		{
			if (m_ObjectForceGenerators[i]->GetType() == type)
			{
				currentGenerator = m_ObjectForceGenerators[i];
				break;
			}
		}

		//Check to see if the desired generator exist
		if (currentGenerator == nullptr)
		{
			return;
		}
		
		//Nested loop so that every object gets paired with eachother, order does not matter
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			for (unsigned int j = i + 1; j < objects.size(); j++)
			{
				mp_ForceRegistry->Add(objects[i], objects[j], currentGenerator);
			}
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::RemoveFromRegistry(std::vector<PhysicsObject*> objects, GeneratorType type)
{
	bool twoObjects = type >= GeneratorType::OBJECT_FORCE_GENERATOR;

	if (!twoObjects)
	{
		ForceGenerator* currentGenerator = nullptr;
		for (unsigned int i = 0; i < m_ForceGenerators.size(); i++)
		{
			if (m_ForceGenerators[i]->GetType() == type)
			{
				currentGenerator = m_ForceGenerators[i];
				break;
			}
		}

		//Check to see if the desired generator exist
		if (currentGenerator == nullptr)
		{
			return;
		}

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			mp_ForceRegistry->Remove(objects[i], currentGenerator);
		}
	}
	else
	{
		ObjectForceGenerator* currentGenerator = nullptr;
		for (unsigned int i = 0; i < m_ObjectForceGenerators.size(); i++)
		{
			if (m_ObjectForceGenerators[i]->GetType() == type)
			{
				currentGenerator = m_ObjectForceGenerators[i];
				break;
			}
		}

		//Check to see if the desired generator exist
		if (currentGenerator == nullptr)
		{
			return;
		}

		//Nested loop so that every object gets paired with eachother, order does not matter
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			for (unsigned int j = i + 1; j < objects.size(); j++)
			{
				mp_ForceRegistry->Remove(objects[i], objects[j], currentGenerator);
			}
		}
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Update(float elapsedTime)
{
	//Update the forces
	mp_ForceRegistry->UpdateForces();
	//Update physics objects
	for (unsigned int i = 0; i < m_PhysicsObjects.size(); i++)
	{
		m_PhysicsObjects[i]->Update(elapsedTime);
	}

	mp_CollisionSystem->CheckCollisions();
	mp_CollisionSystem->ResolveContacts(elapsedTime);
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::Reset()
{
	for (unsigned int i = 0; i < m_PhysicsObjects.size(); i++)
	{
		m_PhysicsObjects[i]->Reset();
	}
}

//--------------------------------------------------------------------------------
void PhysicsObjectSystem::CleanUp()
{
	
	for (unsigned int i = 0; i < m_ForceGenerators.size(); i++)
	{
		delete m_ForceGenerators[i];
	}
	for (unsigned int i = 0; i < m_ObjectForceGenerators.size(); i++)
	{
		delete m_ObjectForceGenerators[i];
	}
	m_PhysicsObjects.clear();
	m_ForceGenerators.clear();
	m_ObjectForceGenerators.clear();

	if (mp_CollisionSystem != nullptr)
	{
		mp_CollisionSystem->CleanUp();
	}
	delete mp_CollisionSystem;
	mp_CollisionSystem = nullptr;
}