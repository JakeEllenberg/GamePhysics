//======================================================================
//File: Ground.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Holds and displays a ground plane
//======================================================================
#include "Ground.h"

//--------------------------------------------------------------------------------
Ground::Ground()
{
	m_Dimensions = Vector3D(50, 0, 50);
}

//--------------------------------------------------------------------------------
Ground::~Ground()
{
}

void Ground::Inititalize(std::string textureName)
{
	RenderObject::Inititalize(1.0f, Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, 1.0f, textureName);
}

//--------------------------------------------------------------------------------
void Ground::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, m_Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-m_Dimensions.X, -m_Dimensions.Y, -m_Dimensions.Z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(m_Dimensions.X, -m_Dimensions.Y, -m_Dimensions.Z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(m_Dimensions.X, -m_Dimensions.Y, m_Dimensions.Z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-m_Dimensions.X, -m_Dimensions.Y, m_Dimensions.Z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}