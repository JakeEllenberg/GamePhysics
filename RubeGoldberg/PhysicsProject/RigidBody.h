//======================================================================
//File: Rigidbody.h
//Author: Jake Ellenberg
//Created: 4/18/2015
//======================================================================
#ifndef RIGIDBODY_H
#define PARTICLE_H
//======================================================================
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix.h"
//======================================================================
class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	static void CalculateTransformMatrix(Matrix& transformMatrix, const Vector3D& position, const Quaternion& orientation);
	void SetInitertiaTensor(const Matrix& inertiaTensor);
	void AddForce(const Vector3D& force);
	void Integrate(float duration);
	void ClearAccumulators();
	void AddForceAtPoint(const Vector3D& force, const Vector3D& point);
	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& point);
	inline bool HasInfinateMass() { return m_InverseMass == 1; };
	inline float GetMass() { return 1.0f / m_InverseMass; };
	Vector3D GetPointInWorldSpace(Vector3D point);
private:
	void calculateDerivedData();
	void transfomrInertiaTensor(Matrix& iitWorld, const Quaternion& quaternion, const Matrix& iitBody, const Matrix& rotationMatrix);
	

	bool m_IsAwake;

	float m_AngularDampening;
	float m_InverseMass;
	float m_LinearDampening;
	
	Vector3D m_Position;
	Vector3D m_Velocity;
	Vector3D m_Acceleration;
	Vector3D m_LastFrameAcceleration;
	Vector3D m_Rotation;
	Vector3D m_ForceAccum;
	Vector3D m_TorqueAccum;

	Quaternion m_Orientation;

	Matrix m_TransformationMatrix;
	Matrix m_InerseInertiaTensor;
	Matrix m_InverseInertiaTensorWorld;
};
#endif