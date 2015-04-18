//======================================================================
//File: Ground.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Holds and displays a ground plane
//======================================================================
#include "RenderObject.h"
//======================================================================
#ifndef GROUND_H
#define GROUND_H
//======================================================================
class Ground : public RenderObject
{
public:
	Ground();
	~Ground();
	virtual void Draw();
	void Inititalize(std::string textureName);
private:
	Vector3D m_Dimensions;
};
#endif
//======================================================================