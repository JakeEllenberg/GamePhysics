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

	m_InverseMass = 1;
	m_Dampening = 1;
	m_Radius = 1.0f;
}

//======================================================================
PhysicsObject::~PhysicsObject()
{
}

//--------------------------------------------------------------------------------
void PhysicsObject::Inititalize(float mass, Vector3D initialPosition, Vector3D initialVelocity, Vector3D initialAcceleration, Vector3D initalRotation, float initalRadius)
{
	m_InitialPosition = initialPosition;
	m_InitialVelocity = initialVelocity;
	m_InitialAcceleration = initialAcceleration;
	m_InitialRotation = initalRotation;
	m_Position = initialPosition;
	m_Velocity = initialVelocity;
	m_Acceleration = initialAcceleration;
	m_Rotation = initalRotation;
	m_InverseMass = mass == 0 ? 1 : 1 / mass;
	m_LastAppliedForce = Vector3D::Zero;
	m_Radius = initalRadius;
}

//--------------------------------------------------------------------------------
void PhysicsObject::Update(float sTime)
{
	//seconds 31557600 per year
	//seconds 86400 per day
	//sTime *= 86400.0f * 1.4f; //seconds per day
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
	m_LastAppliedForce = Vector3D::Zero;
}
//======================================================================