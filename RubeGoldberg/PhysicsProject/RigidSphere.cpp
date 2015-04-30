//======================================================================
//File: RigidSphere.h
//Author: Jake Ellenberg
//Created: 4/26/2015
//======================================================================
#include "RigidSphere.h"

RigidSphere::RigidSphere()
{
	m_RigidType = RigidType::SPHERE;
}


RigidSphere::~RigidSphere()
{
}

void RigidSphere::Inititalize(std::string imageName, float radius, float mass, Vector3D initialPosition)
{
	RigidRender::Inititalize(imageName, mass, initialPosition);
	m_Radius = radius;
	m_RigidType = RigidType::SPHERE;
}

void RigidSphere::drawObject()
{
	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	gluSphere(m_Quad, m_Radius, 32, 32);
}