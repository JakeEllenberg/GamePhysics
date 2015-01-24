//======================================================================
//File: PhysicsObject.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Base object class
//======================================================================
#include "PhysicsObject.h"

//======================================================================
PhysicsObject::PhysicsObject()
{
	m_Position = Vector3D::Zero;
	m_Velocity = Vector3D::Zero;
	m_Acceleration = Vector3D::Zero;
	m_InitialPosition = Vector3D::Zero;
	m_InitialVelocity = Vector3D::Zero;
	m_InitialAcceleration = Vector3D::Zero;
	m_InitialRotation = Vector3D::Zero;
}

//======================================================================
PhysicsObject::~PhysicsObject()
{
}

//--------------------------------------------------------------------------------
void PhysicsObject::Draw()
{
	glPushMatrix();
	float amountRotated = m_Rotation.Magnitude();
	Vector3D normalizedRotation = m_Rotation.Normalized();
	//glRotatef(amountRotated, normalizedRotation.X, normalizedRotation.Y, normalizedRotation.Z);
	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	glutSolidSphere(00.1, 100, 100);
	
	glPopMatrix();
}

//--------------------------------------------------------------------------------
void PhysicsObject::Inititalize(Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initalRotation)
{
	m_InitialPosition = initialPosition;
	m_InitialVelocity = initialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_InitialRotation = initalRotation;
	m_Position = initialPosition;
	m_Velocity = initialVelocity;
	m_Acceleration = initialAcceleration;
	m_Rotation = initalRotation;
}

//--------------------------------------------------------------------------------
void PhysicsObject::Update(int msTime)
{
	m_Position += m_Velocity;
	m_Velocity += m_Acceleration;
}

//--------------------------------------------------------------------------------
void PhysicsObject::Reset()
{
	m_Position = m_InitialPosition;
	m_Velocity = m_InitialVelocity;
	m_Acceleration = m_InitialAcceleration;
}
//======================================================================