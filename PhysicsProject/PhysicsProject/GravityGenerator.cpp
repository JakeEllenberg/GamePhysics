//======================================================================
//File: GravityGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Adds the force for gravity between objects such as planets
//======================================================================
#include "GravityGenerator.h"
#include <math.h>

//======================================================================
float const GravityGenerator::GRAVITY = 6.6726f * pow(10.0f, -11.0f);

//======================================================================
GravityGenerator::GravityGenerator()
{
	m_Type = GeneratorType::GRAVITY_GENERATOR;
}

//--------------------------------------------------------------------------------
GravityGenerator::~GravityGenerator()
{
}

//--------------------------------------------------------------------------------
void GravityGenerator::UpdateForce(PhysicsObject* object1, PhysicsObject* object2)
{
	float distanceSQ = object1->GetPosition().CalculateDistanceSQ(object2->GetPosition());
	Vector3D direction = object2->GetPosition() - object1->GetPosition();
	direction.Normalize();
	float force = ((GRAVITY * object1->GetMass() * object2->GetMass()) / distanceSQ);
	Vector3D gravityOnObject1 = direction * force * 10000;
	Vector3D gravityOnObject2 = gravityOnObject1 * -1;
	object1->AddForce(gravityOnObject1);
	object2->AddForce(gravityOnObject2);
}