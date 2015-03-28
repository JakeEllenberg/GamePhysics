//======================================================================
//File: Level.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Hold level data
//======================================================================
#include "Shape.h"
class Pyramid : public Shape
{
public:
	Pyramid();
	~Pyramid();

	void Inititalize(Vector3D centerPosition, std::string texturePath, float length);
};

