//======================================================================
//File: FireWork.h
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: Particle that may explode into more particles
//======================================================================
#ifndef FIREWORK_H
#define FIREWORK_H
//======================================================================
#include "Particle.h"
//======================================================================
class Firework : public Particle
{
public:
	Firework();
	~Firework();

	virtual void Inititalize(bool isExploding, float lifeTime, Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initalRotation = Vector3D::Zero);
	inline bool CheckExploding() { return m_IsExploding; };
private:
	bool m_IsExploding;
};
#endif
//======================================================================