//======================================================================
//File: Particle.h
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: A Physics object with a life time
//======================================================================
#ifndef PARTICLE_H
#define PARTICLE_H
//======================================================================
#include "PhysicsObject.h"
//======================================================================
class Particle :
	public PhysicsObject
{
public:
	Particle();
	~Particle();
	virtual void Inititalize(int lifeTime, Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initalRotation = Vector3D::Zero);
	virtual void Update(int deltaTime);
	bool CheckAlive();
private:
	int m_MsLifeTime;
};
#endif
//======================================================================
