#include "RigidBodySpringForceGenerator.h"


RigidBodySpringForceGenerator::RigidBodySpringForceGenerator(const Vector3D& localConnectionPoint, RigidBody* anchorObject, const Vector3D &otherConnectionPoint, float springConstant, float restLength)
{
	m_ConnectionPoint = localConnectionPoint;
	m_OtherConnectionPoint = otherConnectionPoint;
	m_AnchorRigidBody = anchorObject;
	m_SpringConstant = springConstant;
	m_RestLength = restLength;
}

RigidBodySpringForceGenerator::~RigidBodySpringForceGenerator()
{
}

void RigidBodySpringForceGenerator::UpdateForce(RigidBody* rigidbodyOne, RigidBody* rigidbodyTwo)
{
	Vector3D lws = rigidbodyOne->GetPointInWorldSpace(m_ConnectionPoint);
	Vector3D ows = m_AnchorRigidBody->GetPointInWorldSpace(m_OtherConnectionPoint);

	Vector3D force = lws - ows;

	float magnitude = force.Magnitude();
	magnitude = abs(magnitude - m_RestLength);
	magnitude *= m_SpringConstant;

	force.Normalize();
	force = force * -magnitude;
	rigidbodyOne->AddForceAtPoint(force, lws);
}