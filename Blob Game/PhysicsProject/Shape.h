//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef GROUNDCONTACTGENERATOR_H
#define GROUNDCONTACTGENERATOR_H
//======================================================================
#include <vector>
#include "PhysicsObject.h"
#include "RodContactGenerator.h"
//======================================================================
class Shape
{
public:
	Shape();
	~Shape();


private:
	std::vector<PhysicsObject*> m_PhysicsObjects;
	std::vector<RodContactGenerator*> m_Rods;
};
#endif
//======================================================================