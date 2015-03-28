//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H
//======================================================================
#include "Shape.h"
//======================================================================
class Tetrahedron :
	public Shape
{
public:
	Tetrahedron();
	~Tetrahedron();

	void Inititalize(Vector3D centerPosition, std::string texturePath, float length);
};
#endif
//======================================================================