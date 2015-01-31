//======================================================================
//File: GravityGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Adds the force for gravity between objects such as planets
//======================================================================
#ifndef GRAVITY_GENERATOR_H
#define GRAVITY_GENERATOR_H
//======================================================================
#include "ObjectForceGenerator.h"
//======================================================================
class GravityGenerator : public ObjectForceGenerator
{
public:
	GravityGenerator();
	~GravityGenerator();
	void UpdateForce(PhysicsObject* object1, PhysicsObject* object2);
private:
	static const float GRAVITY;
};
#endif
//======================================================================