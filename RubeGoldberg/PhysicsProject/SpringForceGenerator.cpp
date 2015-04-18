//======================================================================
//File: SpringContactGenerator.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "SpringForceGenerator.h"
//======================================================================

//--------------------------------------------------------------------------------
SpringForceGenerator::SpringForceGenerator(float k, float length, PhysicsObject* anchorObject)
{
	m_K = k;
	m_RestLength = length;
	m_AnchorObject = anchorObject;
	m_Type = GeneratorType::SPRING_FORCE_GENERATOR;
}

//--------------------------------------------------------------------------------
SpringForceGenerator::~SpringForceGenerator()
{
}

//--------------------------------------------------------------------------------
void SpringForceGenerator::UpdateForce(PhysicsObject* springObject)
{
	Vector3D force;
	force = springObject->GetPosition();
	force -= m_AnchorObject->GetPosition();

	float magnitude = force.Magnitude();
	magnitude = fabs(magnitude - m_RestLength);
	magnitude *= m_K;

	force.Normalize();
	force = force * - magnitude;
	springObject->AddForce(force);
}

//--------------------------------------------------------------------------------
void UpdateForce(RigidBody* rigidbodyOne, RigidBody* rigidbodyTwo = NULL)
{

}
//======================================================================