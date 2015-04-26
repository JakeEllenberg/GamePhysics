//======================================================================
//File: RigidSphere.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#ifndef RIGID_SPHERE_H
#define RIGID_SPHERE_H
//======================================================================
#include "RigidRender.h"
//======================================================================
class RigidSphere : public RigidRender
{
public:
	RigidSphere();
	~RigidSphere();

	virtual void Inititalize(std::string imageName,float radius, float mass = 1, Vector3D initialPosition = Vector3D::Zero);

private:
	virtual void drawObject();

	float m_Radius;
};
#endif;
//======================================================================