//======================================================================
//File: Particle.h
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: A Physics object with a life time
//======================================================================
#include "Particle.h"

//======================================================================
Particle::Particle()
{
	m_MsLifeTime = 0;
}

//======================================================================
Particle::~Particle()
{

}

//--------------------------------------------------------------------------------
void Particle::Inititalize(int lifeTime, Vector3D initialPosition, Vector3D initialVelocity, 
	Vector3D initialAcceleration, Vector3D initalRotation)
{
	PhysicsObject::Inititalize(initialPosition, initialVelocity, initialAcceleration, initalRotation);
	m_MsLifeTime = lifeTime;
}

//--------------------------------------------------------------------------------
void Particle::Update(int deltaTime)
{
	PhysicsObject::Update(deltaTime);

	if (m_MsLifeTime > 0)
	{
		m_MsLifeTime -= deltaTime;
	}
}

//--------------------------------------------------------------------------------
bool Particle::CheckAlive()
{
	return m_MsLifeTime > 0;
}