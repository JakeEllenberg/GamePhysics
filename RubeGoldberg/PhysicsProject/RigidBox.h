//======================================================================
//File: RigidBox.h
//Author: Jake Ellenberg
//Created: 4/30/2015
//======================================================================
#ifndef RIGID_BOX_H
#define RIGID_BOX_H
//======================================================================
#include "RigidRender.h"
//======================================================================
class RigidBox : public RigidRender
{
public:
	RigidBox();
	~RigidBox();

	virtual void Inititalize(std::string imageName, float size, float mass = 1, Vector3D initialPosition = Vector3D::Zero);

	inline float GetSize() { return m_Size; };
private:
	virtual void drawObject();

	float m_Size;
};
#endif