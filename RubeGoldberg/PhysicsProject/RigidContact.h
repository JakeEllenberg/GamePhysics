//======================================================================
//File: RigidContact.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#ifndef RIGIDCONTACT_H
#define RIGIDCONTACT_H
//======================================================================
#include "Vector3D.h"
#include "RigidBody.h"
//======================================================================
class RigidContact
{
public:
	RigidContact();
	~RigidContact();

	void Inititalize(float Restitution, float Friction, Vector3D contactNormal, Vector3D contactPoint, float pentration, RigidBody* bodyOne, RigidBody* bodyTwo = nullptr);

	void CalculateInternals(float duration);
	void CalculateContactBasis();
	Vector3D CalculateLocalVelocity(bool useBodyOne, float duration);
	void CalculateDesiredDeltaVelocity(float duration);

	inline float GetPenetration() { return m_Pentration; };
	inline void SetPenetration(float penetration) { m_Pentration = penetration; };

	void MatchAwakeState();
	void ApplyPositionChange(Vector3D linearChange[2], Vector3D angularChange[2], float penetration, float deltaTime);
	void ApplyVelocityChange(Vector3D velocityChange[2], Vector3D rotationChange[2], float deltaTime);

	inline RigidBody* GetBody(int index) { return index == 0 ? m_BodyOne : m_BodyTwo; };
	inline Vector3D GetRelativePosition(int index) { return index == 0 ? m_RelativePositionOne : m_RelativePositionTwo; };
	inline Vector3D GetContactNormal(){ return m_ContactNormal; };
	inline float GetDesiredDeltaVelocity() { return m_DesiredDeltaVelocity; };
	inline Vector3D GetContactVelocity() { return m_ContactVelocity; };
	inline void SetContactVelocity(Vector3D vel) { m_ContactVelocity = vel; };
	inline Matrix GetContactToWorld() { return m_ContactToWorld; };

private:
	Vector3D calculateFrictionlessImpulse(Matrix* inverseInertiaTensor);
	Vector3D calculateFrictionImpulse(Matrix* inverseInertiaTensor);

	float m_Restitution;
	float m_Friction;
	float m_Pentration;
	Vector3D m_ContactVelocity;
	Vector3D m_ContactNormal;
	Vector3D m_ContactPoint;

	Matrix m_ContactToWorld;

	float m_DesiredDeltaVelocity;

	Vector3D m_RelativePositionOne;
	Vector3D m_RelativePositionTwo;
	
	RigidBody* m_BodyOne;
	RigidBody* m_BodyTwo;

	
};
#endif
//======================================================================