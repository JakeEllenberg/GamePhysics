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
	m_SLifeTime = 0;
}

//======================================================================
Particle::~Particle()
{

}

//--------------------------------------------------------------------------------
void Particle::Inititalize(float lifeTime, Vector3D initialPosition, Vector3D initialVelocity, 
	Vector3D initialAcceleration, Vector3D initalRotation)
{
	PhysicsObject::Inititalize(1.0f, initialPosition, initialVelocity, initialAcceleration, initalRotation);
	m_SLifeTime = lifeTime;
}

//--------------------------------------------------------------------------------
void Particle::Update(float deltaTime)
{
	PhysicsObject::Update(deltaTime);

	if (m_SLifeTime > 0)
	{
		m_SLifeTime -= deltaTime;
	}
}

//--------------------------------------------------------------------------------
bool Particle::CheckAlive()
{
	return m_SLifeTime > 0;
}