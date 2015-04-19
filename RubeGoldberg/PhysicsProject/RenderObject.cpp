#include "RenderObject.h"
#include "SOIL.h"
#include "GameApp.h"
#include <iostream>
#include "ImageHandler.h"

RenderObject::RenderObject()
{
	m_Radius = .1f;
}


RenderObject::~RenderObject()
{
}

void RenderObject::Inititalize(float mass, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initalRotation, float initalRadius, std::string imageFileName)
{
	PhysicsObject::Inititalize(mass, initialPosition, initialVelocity, Vector3D::Zero, initalRotation, initalRadius);
	
	loadImage(imageFileName);
}

void RenderObject::Inititalize(float mass, Vector3D initialPosition, std::string imageName)
{
	PhysicsObject::Inititalize(mass, initialPosition);
	loadImage(imageName);
}

//--------------------------------------------------------------------------------
void RenderObject::loadImage(std::string imageName)
{
	m_Tex = *ImageHandler::GetInstance()->GetImage(imageName);

	m_Quad = gluNewQuadric();
}

//--------------------------------------------------------------------------------
void RenderObject::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_Tex);
	gluQuadricTexture(m_Quad, m_Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluQuadricDrawStyle(m_Quad, GLU_FILL);
	gluQuadricTexture(m_Quad, GL_TRUE);
	gluQuadricNormals(m_Quad, GLU_SMOOTH);

	glPushMatrix();

	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);

	gluSphere(m_Quad, m_Radius, 25, 25);

	glPopMatrix();
}