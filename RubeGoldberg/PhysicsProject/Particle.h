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
	virtual void Inititalize(float lifeTime, Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initalRotation = Vector3D::Zero);
	virtual void Update(float deltaTime);
	bool CheckAlive();
private:
	float m_SLifeTime;
};
#endif
//======================================================================
