//======================================================================
//File: RigidRender.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#ifndef RIGID_RENDER_H
#define RIGID_RENDER_H
//======================================================================
#include "RigidBody.h"
#include <gl\glut.h>
//======================================================================
class RigidRender : public RigidBody
{
public:
	RigidRender();
	~RigidRender();
	void LoadTexture(std::string imageName);
	virtual void Inititalize(std::string imageName, float mass = 1, Vector3D initialPosition = Vector3D::Zero);
	virtual void Draw();
	
protected:
	virtual void drawObject() = 0;
	GLuint m_Tex;
	GLUquadric* m_Quad;
};
#endif
//======================================================================