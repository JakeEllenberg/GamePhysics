//======================================================================
//File: CollisionSystem.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "CollisionSystem.h"

//--------------------------------------------------------------------------------
CollisionSystem::CollisionSystem()
{
	m_PositionIterations = 1;
	m_VelocityIterations = 1;
	m_PositionEpsilon = 0.01f;
	m_VelocityEpsilon = 0.01f;
}

//--------------------------------------------------------------------------------
CollisionSystem::~CollisionSystem()
{
}

//--------------------------------------------------------------------------------
void CollisionSystem::Inititalize(float groundPos)
{
	m_ContactGenerators.push_back(new GroundContactGenerator(groundPos));
	m_Friction = .5f;
	m_Restitution = .5f;
	m_PositionIterations = 1;
	m_VelocityIterations = 1;
	m_PositionEpsilon = 0.01f;
	m_VelocityEpsilon = 0.01f;
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

//--------------------------------------------------------------------------------
void CollisionSystem::AddRigidBodies(std::vector<RigidBody*> bodies)
{
	for each(RigidBody* body in bodies)
	{
		m_RigidBodies.push_back(body);
	}
}
//--------------------------------------------------------------------------------
void CollisionSystem::AddRigidBody(RigidBody* rigidBody)
{
	m_RigidBodies.push_back(rigidBody);
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

void CollisionSystem::AddRigidContact(RigidContact contact)
{ 
	m_RigidContacts.push_back(contact); 
};

//--------------------------------------------------------------------------------
void CollisionSystem::ResolveContacts(float deltaTime)
{
	for each(Contact contact in m_Contacts)
	{
		contact.Resolve(deltaTime);
	}
	m_Contacts.clear();

	resolveRigidContacts(deltaTime);
}

//--------------------------------------------------------------------------------
void CollisionSystem::resolveRigidContacts(float duration)
{
	prepareRigidContacts(duration);
	adjustPosition(duration);
	adjustVelocities(duration);
}
//--------------------------------------------------------------------------------
void CollisionSystem::prepareRigidContacts(float duration)
{
	for each(RigidContact rigidContact in m_RigidContacts)
	{
		rigidContact.CalculateInternals(duration);
	}
}

void CollisionSystem::adjustPosition(float duration)
{
	unsigned int numContacts = m_RigidContacts.size();
	unsigned int i, index;

	Vector3D linearChange[2], angularChange[2];

	float max;
	Vector3D deltaPosition;

	while (m_PositionIterationsUsed < m_PositionIterations)
	{
		max = m_PositionEpsilon;

		index = 0;
		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			if (m_RigidContacts[i].GetPenetration() > max)
			{
				max = m_RigidContacts[i].GetPenetration();
				index = i;
			}
		}
		if (index == m_RigidContacts.size()) 
			break;

		m_RigidContacts[index].MatchAwakeState();

		m_RigidContacts[index].ApplyPositionChange(linearChange, angularChange, max);

		for (i = 0; i < m_RigidContacts.size(); i++)
		{

			for (unsigned int b = 0; b < 2; b++)
			{
				if (m_RigidContacts[i].GetBody(b) == NULL)
				{
					continue;
				}

				for (unsigned int d = 0; d < 2; d++)
				{
					deltaPosition = linearChange[d] + angularChange[d] * m_RigidContacts[i].GetRelativePosition(b);

					float pen = m_RigidContacts[i].GetPenetration();
					pen += ((deltaPosition.Dot(m_RigidContacts[i].GetContactNormal())) * (b ? 1 : -1));
					m_RigidContacts[i].SetPenetration(pen);
				}
			}
		}
		m_PositionIterationsUsed++;
	}
}

void CollisionSystem::adjustVelocities(float duration)
{
	Vector3D velocityChange[2], rotationChange[2];
	Vector3D deltaVelocity;

	m_VelocityIterationsUsed = 0;
	while (m_VelocityIterationsUsed < m_VelocityIterations)
	{
		float max = m_VelocityEpsilon;

		unsigned int index = m_RigidContacts.size();

		for (unsigned int i = 0; i < m_RigidContacts.size(); i++)
		{
			if (m_RigidContacts[i].GetDesiredDeltaVelocity() > max)
			{
				max = m_RigidContacts[i].GetDesiredDeltaVelocity();
				index = i;
			}
		}

		if (index == m_RigidContacts.size())
			break;

		m_RigidContacts[index].MatchAwakeState();
		m_RigidContacts[index].ApplyVelocityChange(velocityChange, rotationChange);

		for (unsigned int i = 0; i < m_RigidContacts.size(); i++)
		{
			for (unsigned int b = 0; b < 2; b++)
			{
				if (m_RigidContacts[i].GetBody(b) == NULL)
				{
					continue;
				}

				for (unsigned d = 0; d < 2; d++)
				{
					if (m_RigidContacts[i].GetBody(b) == m_RigidContacts[index].GetBody(d))
					{
						deltaVelocity = velocityChange[d] + rotationChange[d] * m_RigidContacts[i].GetRelativePosition(b);

						Vector3D conVel = m_RigidContacts[i].GetContactVelocity();
						conVel += m_RigidContacts[i].GetContactToWorld().TransformTranspose(deltaVelocity) * (b ? -1.0f : 1.0f);
						m_RigidContacts[i].SetContactVelocity(conVel);

						m_RigidContacts[i].CalculateDesiredDeltaVelocity(duration);
					}
				}
			}
		}
		m_VelocityIterationsUsed++;
	}
}

//--------------------------------------------------------------------------------
void CollisionSystem::CheckCollisions()
{
	for each(ContactGenerator* contactGenerator in m_ContactGenerators)
	{
		contactGenerator->AddContact(this);
	}

	for each(RigidContactGenerator* generator in m_RigidContactGenerator)
	{
		generator->AddContact(this);
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