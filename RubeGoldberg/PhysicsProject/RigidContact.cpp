//======================================================================
//File: RigidContact.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#include "RigidContact.h"

//======================================================================
RigidContact::RigidContact()
{
}


RigidContact::~RigidContact()
{
}

//======================================================================
void RigidContact::Inititalize(float Restitution, float Friction, Vector3D contactNormal, Vector3D contactPoint, float pentration, RigidBody* bodyOne, RigidBody* bodyTwo)
{
	m_Restitution = Restitution;
	m_Friction = Friction;
	m_ContactNormal = contactNormal;
	m_ContactPoint = contactPoint;
	m_Pentration = pentration;
	m_BodyOne = bodyOne;
	m_BodyTwo = bodyTwo;
}

