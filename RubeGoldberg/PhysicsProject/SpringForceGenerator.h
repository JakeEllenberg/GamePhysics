//======================================================================
//File: SpringContactGenerator.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef SPRING_FORCE_GENERATOR_H
#define SPRING_FORCE_GENERATOR_H
//======================================================================
#include "ForceGenerator.h"
//======================================================================
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(float k, float length, PhysicsObject* anchorObject);
	~SpringForceGenerator();

	virtual void UpdateForce(PhysicsObject* springObject);

protected:
	float m_K;
	float m_RestLength;
	PhysicsObject* m_AnchorObject;
};
//======================================================================
#endif