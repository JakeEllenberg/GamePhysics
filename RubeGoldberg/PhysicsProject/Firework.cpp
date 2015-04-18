//======================================================================
//File: FireWork.h
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: Particle that may explode into more particles
//======================================================================
#include "Firework.h"

Firework::Firework()
{
}


Firework::~Firework()
{
}

//--------------------------------------------------------------------------------
void Firework::Inititalize(bool isExploding, float lifeTime, Vector3D initialPosition, Vector3D initialVelocity,
	Vector3D initialAcceleration, Vector3D initalRotation)
{
	Particle::Inititalize(lifeTime, initialPosition, initialVelocity, initialAcceleration, initalRotation);
	m_IsExploding = isExploding;
}