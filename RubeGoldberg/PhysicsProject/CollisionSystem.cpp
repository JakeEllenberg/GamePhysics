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
	m_Friction = .5f;
	m_Restitution = .1f;
	m_PositionIterations = 1;
	m_VelocityIterations = 1;
	m_PositionEpsilon = 0.0000000001f;
	m_VelocityEpsilon = 0.0000000001f;
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
	

	resolveRigidContacts(deltaTime);

	m_Contacts.clear();
	m_RigidContacts.clear();
}

//--------------------------------------------------------------------------------
void CollisionSystem::resolveRigidContacts(float duration)
{
	prepareRigidContacts(duration);
	adjustPosition(duration);
	adjustVelocities(duration);
	//adjustPositionLikeAParticle(duration);
	//adjustVelocitiesLikeAParticle(duration);
	
}
//--------------------------------------------------------------------------------
void CollisionSystem::prepareRigidContacts(float duration)
{
	for (unsigned int i = 0; i < m_RigidContacts.size(); i++)
	{
		m_RigidContacts[i].CalculateInternals(duration);
	}
}

void CollisionSystem::adjustVelocitiesLikeAParticle(float deltaTime)
{
	unsigned int i;
	unsigned int index;
	Vector3D linearChange[2];
	Vector3D angularChange[2];
	float max;
	Vector3D deltaPosition;
	m_PositionIterationsUsed = 0;
	while (m_PositionIterationsUsed < m_PositionIterations)
	{
		max = m_PositionEpsilon;
		index = m_RigidContacts.size();

		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			float penetration = m_RigidContacts[i].GetPenetration();
			if (penetration > max)
			{
				max = penetration;
				index = i;
			}
		}
		if (index == m_RigidContacts.size())
			break;

		
		RigidBody* bodyOne = m_RigidContacts[index].GetBody(0);
		RigidBody* bodyTwo = m_RigidContacts[index].GetBody(1);
		Vector3D contactNormal = m_RigidContacts[index].GetContactNormal();
		Vector3D relativeVelocity = bodyOne->GetVelocity();
		if (bodyTwo)
		{
			relativeVelocity -= bodyTwo->GetVelocity();
		}

		float separatingVelocity = relativeVelocity.Dot(contactNormal);

		if (separatingVelocity > 0)
		{
			return;
		}

		float newSeparatingVelocity = -separatingVelocity * m_Restitution;

		Vector3D acceleration = bodyOne->GetAcceleration();
		if (bodyTwo != nullptr)
		{
			acceleration -= bodyTwo->GetAcceleration();
		}
		float accumVelocity = acceleration.Dot(contactNormal) * deltaTime;
		if (accumVelocity < 0)
		{
			separatingVelocity -= accumVelocity;
		}

		float deltaVelocity = newSeparatingVelocity - separatingVelocity;

		float totalInverseMass = bodyOne->GetInverseMass();
		if (bodyOne)
		{
			totalInverseMass += bodyOne->GetInverseMass();
		}

		if (totalInverseMass <= 0)
		{
			return;
		}

		float impulse = deltaVelocity / totalInverseMass;
		Vector3D impulsePerIMass = contactNormal * impulse;

		bodyOne->SetVelocity(bodyOne->GetVelocity() + impulsePerIMass * bodyOne->GetInverseMass());
		if (bodyTwo)
		{
			bodyTwo->SetVelocity(bodyTwo->GetVelocity() + impulsePerIMass * -bodyTwo->GetInverseMass());
		}
	}
}
void CollisionSystem::adjustPositionLikeAParticle(float deltaTime)
{
	unsigned int i;
	unsigned int index;
	Vector3D linearChange[2];
	Vector3D angularChange[2];
	float max;
	Vector3D deltaPosition;
	m_PositionIterationsUsed = 0;
	while (m_PositionIterationsUsed < m_PositionIterations)
	{
		max = m_PositionEpsilon;
		index = m_RigidContacts.size();

		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			float penetration = m_RigidContacts[i].GetPenetration();
			if (penetration > max)
			{
				max = penetration;
				index = i;
			}
		}
		if (index == m_RigidContacts.size())
			break;


		RigidBody* bodyOne = m_RigidContacts[index].GetBody(0);
		RigidBody* bodyTwo = m_RigidContacts[index].GetBody(1);
		Vector3D contactNormal = m_RigidContacts[index].GetContactNormal();
		Vector3D relativeVelocity = bodyOne->GetVelocity();
		float penetration = m_RigidContacts[index].GetPenetration();

		if (penetration <= 0)
		{
			return;
		}

		float totalInverseMass = bodyOne->GetInverseMass();

		if (bodyTwo != nullptr)
		{
			totalInverseMass += bodyTwo->GetInverseMass();
		}

		if (totalInverseMass <= 0)
		{
			return;
		}

		Vector3D movePerIMass = contactNormal * (penetration / totalInverseMass);
		Vector3D particleMovementOne = movePerIMass * bodyOne->GetInverseMass() * deltaTime;
		bodyOne->SetPosition(bodyOne->GetPosition() + particleMovementOne);
		Vector3D particleMovementTwo = Vector3D::Zero;
		if (bodyTwo != nullptr)
		{
			particleMovementTwo = movePerIMass * -bodyTwo->GetInverseMass() * deltaTime;
			bodyTwo->SetPosition(bodyTwo->GetPosition() + particleMovementTwo);
		}
	}
}

//-----------------------------------------------------------------------------
void CollisionSystem::adjustPosition(float deltaTime)
{
	unsigned int i;
	unsigned int index;
	Vector3D linearChange[2];
	Vector3D angularChange[2];
	float max;
	Vector3D deltaPosition;

	m_PositionIterationsUsed = 0;
	while (m_PositionIterationsUsed < m_PositionIterations)
	{
		max = m_PositionEpsilon;
		index = m_RigidContacts.size();

		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			float penetration = m_RigidContacts[i].GetPenetration();
			if (penetration > max)
			{
				max = penetration;
				index = i;
			}
		}
		if (index == m_RigidContacts.size())
			break;

		m_RigidContacts[index].MatchAwakeState();
		m_RigidContacts[index].ApplyPositionChange(linearChange, angularChange, max, deltaTime);

		for (i = 0; i < m_RigidContacts.size(); i++)
		{
			for (unsigned int body = 0; body < 2; body++)
			{
				if (m_RigidContacts[i].GetBody(body))
				{
					for (unsigned int d = 0; d < 2; d++)
					{
						if (m_RigidContacts[i].GetBody(body) == m_RigidContacts[index].GetBody(d))
						{
							deltaPosition = linearChange[d] + angularChange[d] * m_RigidContacts[i].GetRelativePosition(body);

							float penetration = m_RigidContacts[i].GetPenetration();
							penetration += deltaPosition.Dot(m_RigidContacts[i].GetContactNormal()) * (body ? 1 : -1);
							m_RigidContacts[i].SetPenetration(penetration);
						}
					}
				}
			}
		}
		m_PositionIterationsUsed++;
	}
}


//-----------------------------------------------------------------------------
void CollisionSystem::adjustVelocities(float deltaTime)
{
	Vector3D velocityChange[2];
	Vector3D rotationChange[2];
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
		m_RigidContacts[index].ApplyVelocityChange(velocityChange, rotationChange, deltaTime);

		for (unsigned int i = 0; i < m_RigidContacts.size(); i++)
		{
			for (unsigned int b = 0; b < 2; b++)
			{
				if (m_RigidContacts[i].GetBody(b))
				{
					for (unsigned d = 0; d < 2; d++)
					{
						if (m_RigidContacts[i].GetBody(b) == m_RigidContacts[index].GetBody(d))
						{
							deltaVelocity = velocityChange[d] + rotationChange[d] * m_RigidContacts[i].GetRelativePosition(b);

							m_RigidContacts[i].SetContactVelocity(m_RigidContacts[i].GetContactVelocity() + m_RigidContacts[i].GetContactToWorld().TransformTranspose(deltaVelocity) * (float)(b ? -1 : 1));
							m_RigidContacts[i].CalculateDesiredDeltaVelocity(deltaTime);
						}
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