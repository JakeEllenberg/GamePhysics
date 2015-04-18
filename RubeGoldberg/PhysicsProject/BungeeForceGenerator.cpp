//======================================================================
//File: BungeeForceGenerator.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "BungeeForceGenerator.h"

//======================================================================
BungeeForceGenerator::BungeeForceGenerator(float k, float length, PhysicsObject* anchorObject)
:SpringForceGenerator(k, length, anchorObject)
{
	m_Type = GeneratorType::BUNGEE_FORCE_GENERATOR;
}

//--------------------------------------------------------------------------------
BungeeForceGenerator::~BungeeForceGenerator()
{
}

//--------------------------------------------------------------------------------
void BungeeForceGenerator::UpdateForce(PhysicsObject* springObject)
{
	Vector3D force;
	force = springObject->GetPosition();
	force -= m_AnchorObject->GetPosition();

	float magnitude = force.Magnitude();
	if (magnitude <= m_RestLength) 
	{
		return;
	}
	magnitude = m_K * (magnitude - m_RestLength);

	force.Normalize();
	force = force * -magnitude;
	springObject->AddForce(force);
}
//======================================================================