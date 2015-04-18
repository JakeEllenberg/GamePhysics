//======================================================================
//File: ObjetForceGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Base class for force generators
//======================================================================
#ifndef OBJECTFORCE_GENERATOR_H
#define OBJECTFORCE_GENERATOR_H
//======================================================================
#include "PhysicsObject.h"
#include "Generator.h"
#include <string>
//======================================================================
class ObjectForceGenerator : public Generator
{
public:
	ObjectForceGenerator();
	~ObjectForceGenerator();

	virtual void UpdateForce(PhysicsObject* object1, PhysicsObject* object2) = 0;
};
#endif
//======================================================================