//======================================================================
//File: PhysicsObject.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Defines extra infromation for planets
//======================================================================
#include "Planet.h"

//======================================================================
Planet::Planet()
{
}

//--------------------------------------------------------------------------------
Planet::~Planet()
{
}

//--------------------------------------------------------------------------------
void Planet::Initialize(float radius, float mass, Vector3D initalPosition, Vector3D velocity, std::string planetName)
{
	PhysicsObject::Inititalize(mass, initalPosition, velocity, Vector3D::Zero, Vector3D::Zero, radius);
	m_Name = planetName;
}