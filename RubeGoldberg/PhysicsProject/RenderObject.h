//======================================================================
//File: PhysicsObject.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Extends a physicsobject and allows it to render
//======================================================================
#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H
//======================================================================
#include "PhysicsObject.h"

class RenderObject : public PhysicsObject
{
public:
	RenderObject();
	~RenderObject();

	virtual void Inititalize(float mass = 1, Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initalRotation = Vector3D::Zero, float initalRadius = 0.1f, std::string imageFileName = "");
	virtual void Inititalize(float mass = 1, Vector3D initialPosition = Vector3D::Zero, std::string imageFileName = "");
	virtual void Draw();
	void loadImage(std::string filePath);
	
protected:
	GLuint m_Tex;
	GLUquadric* m_Quad;
};
#endif