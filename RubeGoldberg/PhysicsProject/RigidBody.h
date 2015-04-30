//======================================================================
//File: Rigidbody.h
//Author: Jake Ellenberg
//Created: 4/18/2015
//======================================================================
#ifndef RIGIDBODY_H
#define RIGIDBODY_H
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

	virtual void Inititalize(float mass = 1, Vector3D initialPosition = Vector3D::Zero, Vector3D initialVelocity = Vector3D::Zero, Vector3D initialAcceleration = Vector3D::Zero, Vector3D initalRotation = Vector3D::Zero, float dampening = 1.0f, float angularDampening = 1.0f);
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
	void Reset();
	inline Matrix& GetTransformationMatrix() { return m_TransformationMatrix; };
	inline Vector3D GetPosition() { return m_Position; };

	inline Vector3D GetRotation() { return m_Rotation; };
	inline Vector3D GetVelocity() { return m_Velocity; };
	inline Vector3D GetLastFrameAcc() { return m_LastFrameAcceleration; };
	inline bool GetAwake() { return m_IsAwake; };
	inline void SetAwake(bool awake) { m_IsAwake = awake; };

	void GetInverseInertiaTensorWorld(Matrix* inverseInertiaTensor);

	inline void SetPosition(Vector3D pos) { m_Position = pos; };

	void CalculateDerivedData();

	inline Quaternion GetOrientation() { return m_Orientation; };
	inline void SetOrientation(Quaternion q) { m_Orientation = q; };

	inline float GetInverseMass() { return m_InverseMass; };

	inline void AddVelocity(Vector3D amount) { m_Velocity += amount; };
	inline void AddRotation(Vector3D amount) { m_Rotation += amount; };

	inline Vector3D GetAcceleration() { return m_Acceleration; };

	inline void SetVelocity(Vector3D vel) { m_Velocity = vel; };
protected:
	
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

	Vector3D m_InitPosition;
	Vector3D m_InitVelocity;
	Vector3D m_InitAcceleration;
	Vector3D m_InitRotation;

	Quaternion m_Orientation;

	Matrix m_TransformationMatrix;
	Matrix m_InerseInertiaTensor;
	Matrix m_InverseInertiaTensorWorld;
};
#endif