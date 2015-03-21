//======================================================================
//File: Contact.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "Contact.h"

//--------------------------------------------------------------------------------
Contact::Contact()
{
}

//--------------------------------------------------------------------------------
Contact::~Contact()
{
}

//--------------------------------------------------------------------------------
Contact::Contact(float restitution, Vector3D contactNormal, float penetration, PhysicsObject* contactOne, PhysicsObject* contactTwo)
{
	m_Penetration = penetration;
	m_Restitution = restitution;
	m_ContactNormal = contactNormal;

	mp_ContactOne = contactOne;
	mp_ContactTwo = contactTwo;
}

//-----------------------------------------------------------------------------
void Contact::Resolve(float deltaTime)
{
	resolveVelocity(deltaTime);
	resolveInterpenetration(deltaTime);
}

//-----------------------------------------------------------------------------
void Contact::resolveVelocity(float deltaTime)
{
	float separatingVelocity = calculateSeparatingVelocity();

	if (separatingVelocity > 0)
	{
		return;
	}

	float newSeparatingVelocity = -separatingVelocity * m_Restitution;

	Vector3D acceleration = mp_ContactOne->GetAcceleration();
	if (mp_ContactTwo != nullptr)
	{
		acceleration -= mp_ContactTwo->GetAcceleration();
	}
	float accumVelocity = acceleration.Dot(m_ContactNormal) * deltaTime;
	if (accumVelocity < 0)
	{
		separatingVelocity -= accumVelocity;
	}

	float deltaVelocity = newSeparatingVelocity - separatingVelocity;

	float totalInverseMass = mp_ContactOne->GetInverseMass();
	if (mp_ContactTwo)
	{
		totalInverseMass += mp_ContactTwo->GetInverseMass();
	}

	if (totalInverseMass <= 0)
	{
		return;
	}

	float impulse = deltaVelocity / totalInverseMass;
	Vector3D impulsePerIMass = m_ContactNormal * impulse;

	mp_ContactOne->SetVelocity(mp_ContactOne->GetVelocity() + impulsePerIMass * mp_ContactOne->GetInverseMass());
	if (mp_ContactTwo)
	{
		mp_ContactTwo->SetVelocity(mp_ContactTwo->GetVelocity() + impulsePerIMass * -mp_ContactTwo->GetInverseMass());
	}
}

//-----------------------------------------------------------------------------
void Contact::resolveInterpenetration(float deltaTime)
{
	
	if (m_Penetration <= 0)
	{
		return;
	}

	float totalInverseMass = mp_ContactOne->GetInverseMass();

	if (mp_ContactTwo != nullptr)
	{
		totalInverseMass += mp_ContactTwo->GetInverseMass();
	}

	if (totalInverseMass <= 0)
	{
		return;
	}

	Vector3D movePerIMass = m_ContactNormal * (m_Penetration / totalInverseMass);
	Vector3D particleMovementOne = movePerIMass * mp_ContactOne->GetInverseMass();
	mp_ContactOne->SetPosition(mp_ContactOne->GetPosition() + particleMovementOne);
	Vector3D particleMovementTwo = Vector3D::Zero;
	if (mp_ContactTwo != nullptr)
	{
		particleMovementTwo = movePerIMass * -mp_ContactTwo->GetInverseMass();
		mp_ContactTwo->SetPosition(mp_ContactTwo->GetPosition() + particleMovementTwo);
	}
	
}

//-----------------------------------------------------------------------------
float Contact::calculateSeparatingVelocity()
{
	Vector3D relativeVelocity = mp_ContactOne->GetVelocity();
	if (mp_ContactTwo)
	{
		relativeVelocity -= mp_ContactTwo->GetVelocity();
	}

	return relativeVelocity.Dot(m_ContactNormal);
}
//=============================================================================