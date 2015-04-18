//======================================================================
//File: ForceGenerator.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Base class for force generators
//======================================================================
#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H
//======================================================================
#include "PhysicsObject.h"
#include "Generator.h"
//======================================================================
class ForceGenerator : public Generator
{
public:
	ForceGenerator();
	~ForceGenerator();

	virtual void UpdateForce(PhysicsObject* object) = 0;
};
#endif
//======================================================================