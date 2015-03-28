//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef CUBE_H
#define CUBE_H
//======================================================================
#include "Shape.h"
//======================================================================

class Cube : public Shape
{
public:
	Cube();
	~Cube();

	void Inititalize(Vector3D centerPosition, std::string texturePath, float length);
};
#endif 
//======================================================================