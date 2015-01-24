//======================================================================
//File: PhysicsObject.h
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Base object class
//======================================================================
#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
//======================================================================
#include "Vector3D.h"
#include "Matrix.h"
#include <gl\glut.h>
//======================================================================
class PhysicsObject
{
public:
	PhysicsObject();
	~PhysicsObject();
	virtual void Inititalize(Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initalRotation = Vector3D::Zero);
	virtual void Update(int msTime);
	virtual void Draw();
	virtual void Reset();

	inline void SetPosition(Vector3D position) { m_Position = position; };
	inline void SetVelocity(Vector3D velocity) { m_Velocity = velocity; };
	inline void SetAcceleration(Vector3D acceleration) { m_Acceleration = acceleration; };

	inline Vector3D GetPosition() { return m_Position; };
	inline Vector3D GetVelocity() { return m_Velocity; };
	inline Vector3D GetAcceleration() { return m_Acceleration; };

protected:
	Vector3D m_Position;
	Vector3D m_Velocity;
	Vector3D m_Acceleration;
	Vector3D m_Rotation;
	Vector3D m_InitialPosition;
	Vector3D m_InitialVelocity;
	Vector3D m_InitialAcceleration;
	Vector3D m_InitialRotation;
};
//======================================================================
#endif