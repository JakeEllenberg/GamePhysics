//======================================================================
//File: RigidRender.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#include "RigidRender.h"
#include "ImageHandler.h"


RigidRender::RigidRender()
{
	m_RigidType = RigidType::NONE;
}


RigidRender::~RigidRender()
{
}

void RigidRender::Inititalize(std::string imageName, float mass, Vector3D initialPosition)
{
	RigidBody::Inititalize(mass, initialPosition);
	LoadTexture(imageName);
}

void RigidRender::LoadTexture(std::string imageName)
{
	m_Tex = *ImageHandler::GetInstance()->GetImage(imageName);

	m_Quad = gluNewQuadric();
}

void RigidRender::Draw()
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
	drawObject();
	glPopMatrix();
}