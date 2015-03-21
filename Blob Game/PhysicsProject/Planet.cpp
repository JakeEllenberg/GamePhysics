//======================================================================
//File: PhysicsObject.h
//Author: Jake Ellenberg
//Created: 1/31/2015
//Purpose: Defines extra infromation for planets
//======================================================================
#include "Planet.h"
#include "SOIL.h"
#include "GameApp.h"
#include <iostream>

//======================================================================
Planet::Planet()
{
}

//--------------------------------------------------------------------------------
Planet::~Planet()
{
}

//--------------------------------------------------------------------------------
void Planet::Initialize(float mass, Vector3D initalPosition, Vector3D velocity, std::string planetName, std::string fileName)
{
	PhysicsObject::Inititalize(mass, initalPosition, velocity, Vector3D::Zero, Vector3D::Zero);
	m_Name = planetName;
	loadImage(fileName);
}

void Planet::Update(float sTime)
{
	
	if (GameApp::DebugData)
	{
		std::cout << "Planet: " << m_Name << " position, " << m_Position.ToString() << " velocity " << m_Velocity.ToString()
			<< " acceleartion " << m_Acceleration.ToString() << " total force " << m_LastAppliedForce.ToString() << std::endl;
	}
	PhysicsObject::Update(sTime);
}

//--------------------------------------------------------------------------------
void Planet::loadImage(std::string filePath)
{
	glEnable(GL_TEXTURE_2D);
	int width;
	int height;

	glGenTextures(1, &m_Tex);
	glBindTexture(GL_TEXTURE_2D, m_Tex);

	unsigned char* image = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	m_Quad = gluNewQuadric();
}

void Planet::Draw()
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