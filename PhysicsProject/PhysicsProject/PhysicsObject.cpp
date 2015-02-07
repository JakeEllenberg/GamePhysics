//======================================================================
//File: PhysicsObject.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Base object class
//======================================================================
#include "PhysicsObject.h"
#include "GameApp.h"

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
	m_LastAppliedForce = Vector3D::Zero;
	m_Radius = .1f;
	m_InitalRadius = .1f;
	m_InverseMass = 1;
	m_Dampening = 1;
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
	glutSolidSphere(m_Radius, 10, 10);
	
	glPopMatrix();
}

//--------------------------------------------------------------------------------
void PhysicsObject::Inititalize(float mass, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initalRotation, float radius)
{
	m_InitialPosition = initialPosition;
	m_InitialVelocity = initialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_InitialRotation = initalRotation;
	m_InitalRadius = radius;
	m_Position = initialPosition;
	m_Velocity = initialVelocity;
	m_Acceleration = initialAcceleration;
	m_Rotation = initalRotation;
	m_InverseMass = mass == 0 ? 1 : 1 / mass;
	m_Radius = radius;
	m_LastAppliedForce = Vector3D::Zero;
}

//--------------------------------------------------------------------------------
void PhysicsObject::Update(float sTime)
{
	//seconds 31557600 per year
	//seconds 86400 per day
	sTime *= 86400; //seconds per day
	m_Position += m_Velocity * sTime;
	m_Acceleration = m_LastAppliedForce * (m_InverseMass);
	m_Velocity += m_Acceleration * sTime;
	m_Velocity = m_Velocity * m_Dampening;
	
	m_LastAppliedForce = Vector3D::Zero;
}

//--------------------------------------------------------------------------------
void PhysicsObject::Reset()
{
	m_Position = m_InitialPosition;
	m_Velocity = m_InitialVelocity;
	m_Acceleration = m_InitialAcceleration;
	m_Rotation = m_InitialRotation;
	m_Radius = m_InitalRadius;
	m_LastAppliedForce = Vector3D::Zero;
}
//======================================================================