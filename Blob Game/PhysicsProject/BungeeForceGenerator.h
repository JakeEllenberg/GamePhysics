//======================================================================
//File: BungeeForceGenerator.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef BUNGEE_FORCE_GENERATOR_H
#define BUNGEE_FORCE_GENERATOR_H
//======================================================================
#include "SpringForceGenerator.h"
//======================================================================
class BungeeForceGenerator : public SpringForceGenerator
{
public:
	BungeeForceGenerator(float k, float length, PhysicsObject* anchorObject);
	~BungeeForceGenerator();

	void UpdateForce(PhysicsObject* bungeeObject);
};
#endif
//======================================================================