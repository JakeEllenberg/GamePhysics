//======================================================================
//File: RigidContact.h
//Author: Jake Ellenberg
//Created: 4/22/2015
//======================================================================
#include "RigidContact.h"
#include <math.h>

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

//----------------------------------------------------------------------------------------
void RigidContact::CalculateInternals(float duration)
{
	CalculateContactBasis();

	m_RelativePositionOne = m_ContactPoint - m_BodyOne->GetPosition();
	if (m_BodyTwo != NULL)
	{
		m_RelativePositionTwo = m_ContactPoint - m_BodyTwo->GetPosition();
	}

	m_ContactVelocity = CalculateLocalVelocity(true, duration);

	if (m_BodyTwo != NULL)
	{
		m_ContactVelocity -= CalculateLocalVelocity(false, duration);
	}

	CalculateDesiredDeltaVelocity(duration);
}

//----------------------------------------------------------------------------------------
void RigidContact::CalculateDesiredDeltaVelocity(float duration)
{
	const float velocityLimit = 0.25f;

	float velocityFromAcc = 0;

	if (m_BodyOne->GetAwake())
	{
		velocityFromAcc += m_BodyOne->GetLastFrameAcc().Dot(m_ContactNormal) * duration;
	}

	if (m_BodyTwo != NULL && m_BodyTwo->GetAwake())
	{
		velocityFromAcc = m_BodyTwo->GetLastFrameAcc().Dot(m_ContactNormal) * duration;
	}

	float restitution = m_Restitution;

	if (abs(m_ContactVelocity.X) < velocityLimit)
	{
		restitution = 0.0f;
	}

	m_DesiredDeltaVelocity = -m_ContactVelocity.X - restitution * (m_ContactVelocity.X - velocityFromAcc);
}

//----------------------------------------------------------------------------------------
Vector3D RigidContact::CalculateLocalVelocity(bool useBodyOne, float duration)
{
	RigidBody* body = useBodyOne ? m_BodyOne : m_BodyTwo;
	Vector3D relativePosition = useBodyOne ? m_RelativePositionOne : m_RelativePositionTwo;

	Vector3D velocity = body->GetRotation().Cross(relativePosition);
	velocity += body->GetVelocity();

	Vector3D contactVelocity = m_ContactToWorld.TransformTranspose(velocity);

	Vector3D accVelocity = body->GetLastFrameAcc() * duration;

	accVelocity = m_ContactToWorld.TransformTranspose(accVelocity);

	accVelocity.X = 0;

	contactVelocity += accVelocity;

	return contactVelocity;
}
//----------------------------------------------------------------------------------------
void RigidContact::CalculateContactBasis()
{
	Vector3D contactTangentOne;
	Vector3D contactTangentTwo;

	if (abs(m_ContactNormal.X) > abs(m_ContactNormal.Y))
	{
		const float s = 1.0f / sqrt(m_ContactNormal.Z* m_ContactNormal.Z + m_ContactNormal.X * m_ContactNormal.X);

		contactTangentOne.X = m_ContactNormal.Z * s;
		contactTangentOne.Y = 0;
		contactTangentOne.Z = -m_ContactNormal.X * s;

		contactTangentTwo.X = m_ContactNormal.Y * contactTangentOne.X;
		contactTangentTwo.Y = m_ContactNormal.Z * contactTangentOne.X - m_ContactNormal.X * contactTangentOne.Z;
		contactTangentTwo.Z = -m_ContactNormal.Y * contactTangentOne.X;
	}
	else
	{
		const float s = 1.0f / sqrt(m_ContactNormal.Z* m_ContactNormal.Z + m_ContactNormal.Y * m_ContactNormal.Y);

		contactTangentOne.X = 0;
		contactTangentOne.Y = -m_ContactNormal.Z * s;
		contactTangentOne.Z = m_ContactNormal.Y * s;

		contactTangentTwo.X = m_ContactNormal.Y * contactTangentOne.Z - m_ContactNormal.Z * contactTangentOne.Y;
		contactTangentTwo.Y = -m_ContactNormal.X * contactTangentOne.Z;
		contactTangentTwo.Z = m_ContactNormal.X * contactTangentOne.Y;
	}

	m_ContactToWorld = Matrix(3, 3);

	m_ContactToWorld.Set(0, m_ContactNormal.X);
	m_ContactToWorld.Set(1, contactTangentOne.X);
	m_ContactToWorld.Set(2, contactTangentTwo.X);
	m_ContactToWorld.Set(3, m_ContactNormal.Y);
	m_ContactToWorld.Set(4, contactTangentOne.Y);
	m_ContactToWorld.Set(5, contactTangentTwo.Y);
	m_ContactToWorld.Set(6, m_ContactNormal.Z);
	m_ContactToWorld.Set(7, contactTangentOne.Z);
	m_ContactToWorld.Set(8, contactTangentTwo.Z);
}

//----------------------------------------------------------------------------------------
void RigidContact::MatchAwakeState()
{
	if (m_BodyTwo == NULL) return;

	if (!m_BodyOne->GetAwake() && !m_BodyTwo->GetAwake())
	{
		return;
	}
	
	if (m_BodyOne->GetAwake())
	{
		m_BodyTwo->SetAwake(true);
	}
	else
	{
		m_BodyOne->SetAwake(true);
	}
}

void RigidContact::ApplyPositionChange(Vector3D linearChange[2], Vector3D angularChange[2], float penetration, float deltaTime)
{
	const float angularLimit = 0.2f;
	float angularMove[2];
	float linearMove[2];

	float totalInertia = 0;
	float linearInertia[2];
	float angularInertia[2];

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0 && m_BodyOne || i == 1 && m_BodyTwo)
		{
			RigidBody* rigidBody;
			Vector3D relativeContactPosition;
			if (i == 0)
			{
				rigidBody = m_BodyOne;
				relativeContactPosition = m_RelativePositionOne;
			}
			else
			{
				rigidBody = m_BodyTwo;
				relativeContactPosition = m_RelativePositionTwo;
			}

			Matrix inverseInertiaTensor = Matrix(3, 3);
			rigidBody->GetInverseInertiaTensorWorld(&inverseInertiaTensor);

			Vector3D angularInertiaWorld = relativeContactPosition.Cross(m_ContactNormal);
			angularInertiaWorld = inverseInertiaTensor.Transform(angularInertiaWorld);
			angularInertiaWorld = angularInertiaWorld.Cross(relativeContactPosition);
			angularInertia[i] = angularInertiaWorld.Dot(m_ContactNormal);

			linearInertia[i] = rigidBody->GetInverseMass();

			totalInertia += linearInertia[i] + angularInertia[i];
		}
	}

	for (unsigned int i = 0; i < 2; i++)
	{
		if (i == 0 && m_BodyOne || i == 1 && m_BodyTwo)
		{
			RigidBody* rigidBody;
			Vector3D relativeContactPosition;
			if (i == 0)
			{
				rigidBody = m_BodyOne;
				relativeContactPosition = m_RelativePositionOne;
			}
			else
			{
				rigidBody = m_BodyTwo;
				relativeContactPosition = m_RelativePositionTwo;
			}

			int sign = (i == 0) ? 1 : -1;
			angularMove[i] = sign * m_Pentration * (angularInertia[i] / totalInertia);
			linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

			Vector3D projection = relativeContactPosition;
			projection += m_ContactNormal * ((relativeContactPosition * -1) * m_ContactNormal);

			float maxMagnitude = angularLimit * projection.Magnitude();

			if (angularMove[i] < -maxMagnitude)
			{
				float totalMove = angularMove[i] + linearMove[i];
				angularMove[i] = -maxMagnitude;
				linearMove[i] = totalMove - angularMove[i];
			}
			else if (angularMove[i] > maxMagnitude)
			{
				float totalMove = angularMove[i] + linearMove[i];
				angularMove[i] = maxMagnitude;
				linearMove[i] = totalMove - angularMove[i];
			}

			if (angularMove[i] == 0)
			{
				angularChange[i] = Vector3D::Zero;
			}
			else
			{
				Vector3D targetAngularDirection = relativeContactPosition * m_ContactNormal;

				Matrix inverseInertiaTensor = Matrix(3, 3);
				rigidBody->GetInverseInertiaTensorWorld(&inverseInertiaTensor);

				angularChange[i] = inverseInertiaTensor.Transform(targetAngularDirection) * (angularMove[i] / angularInertia[i]);
			}

			linearChange[i] = m_ContactNormal * linearMove[i];

			Vector3D position = rigidBody->GetPosition();
			position += (m_ContactNormal * linearMove[i]) * deltaTime; //hacky change
			rigidBody->SetPosition(position);

			Quaternion q;
			q = rigidBody->GetOrientation();
			q.AddScaledVector(angularChange[i] * deltaTime, 1.0f);
			rigidBody->SetOrientation(q);

			if (!rigidBody->GetAwake())
				rigidBody->CalculateDerivedData();
		}
	}
}

//-----------------------------------------------------------------------------
void RigidContact::ApplyVelocityChange(Vector3D velocityChange[2], Vector3D rotationChange[2], float deltaTime)
{
	Matrix inverseInertiaTensor[2];
	m_BodyOne->GetInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
	if (m_BodyTwo)
		m_BodyTwo->GetInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

	Vector3D impulseContact;

	if (m_Friction == 0.0f)
	{
		impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
	}
	else
	{
		//impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
		impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
	}

	Vector3D impulse = m_ContactToWorld.Transform(impulseContact);

	Vector3D impulsiveTorque = m_RelativePositionOne.Cross(impulse);
	rotationChange[0] = inverseInertiaTensor[0].Transform(impulsiveTorque);
	velocityChange[0] = Vector3D::Zero;
	velocityChange[0] += impulse * m_BodyOne->GetInverseMass();

	m_BodyOne->AddVelocity(velocityChange[0]);
	m_BodyOne->AddRotation(rotationChange[0]);

	if (m_BodyTwo)
	{
		Vector3D impulsiveTorque = impulse.Cross(m_RelativePositionTwo);
		rotationChange[1] = inverseInertiaTensor[1].Transform(impulsiveTorque);
		velocityChange[1] = Vector3D::Zero;
		velocityChange[1] += impulse * -m_BodyTwo->GetInverseMass();

		m_BodyTwo->AddVelocity(velocityChange[1]);
		m_BodyTwo->AddRotation(rotationChange[1]);
	}
}

Vector3D RigidContact::calculateFrictionlessImpulse(Matrix* inverseInertiaTensor)
{
	Vector3D impulseContact;

	Vector3D deltaVelocityWorld = m_RelativePositionOne.Cross(m_ContactNormal);
	deltaVelocityWorld = inverseInertiaTensor[0].Transform(deltaVelocityWorld);
	deltaVelocityWorld = deltaVelocityWorld.Cross(m_RelativePositionOne);

	float deltaVelocity = deltaVelocityWorld.Dot(m_ContactNormal);

	deltaVelocity += 1 / m_BodyOne->GetMass();

	if (m_BodyTwo != NULL)
	{
		Vector3D deltaVelocityWorld = m_RelativePositionTwo.Cross(m_ContactNormal);
		deltaVelocityWorld = inverseInertiaTensor[1].Transform(deltaVelocityWorld);
		deltaVelocityWorld = deltaVelocityWorld.Cross(m_RelativePositionTwo);

		float deltaVelocity = deltaVelocityWorld.Dot(m_ContactNormal);

		deltaVelocity += 1 / m_BodyOne->GetMass();
	}

	impulseContact.X = m_DesiredDeltaVelocity / deltaVelocity;
	impulseContact.Y = 0;
	impulseContact.Z = 0;

	return impulseContact;
}

Vector3D RigidContact::calculateFrictionImpulse(Matrix* inverseInertiaTensor)
{
	Vector3D impulseContact;
	float inverseMass = 1 / m_BodyOne->GetMass();

	Matrix impulseToTorque = Matrix(3, 3);
	impulseToTorque.SetSkewSymetric(m_RelativePositionOne);

	Matrix deltaVelocityWorld = impulseToTorque;
	deltaVelocityWorld = deltaVelocityWorld * inverseInertiaTensor[0];
	deltaVelocityWorld = deltaVelocityWorld * impulseToTorque;
	deltaVelocityWorld = deltaVelocityWorld * -1;

	if (m_BodyTwo != NULL)
	{
		impulseToTorque.SetSkewSymetric(m_RelativePositionTwo);

		Matrix deltaVelocityWorld2 = impulseToTorque;
		deltaVelocityWorld2 = deltaVelocityWorld2 * inverseInertiaTensor[0];
		deltaVelocityWorld2 = deltaVelocityWorld2 * impulseToTorque;
		deltaVelocityWorld2 = deltaVelocityWorld2 * -1;

		deltaVelocityWorld = deltaVelocityWorld + deltaVelocityWorld2;

		inverseMass += 1 / m_BodyTwo->GetMass();
	}

	Matrix deltaVelocity = m_ContactToWorld.TransposeMatrix();
	deltaVelocity = deltaVelocity * deltaVelocityWorld;
	deltaVelocity = deltaVelocity * m_ContactToWorld;

	deltaVelocity.Set(0, deltaVelocity.Get(0) + inverseMass);
	deltaVelocity.Set(4, deltaVelocity.Get(4) + inverseMass);
	deltaVelocity.Set(8, deltaVelocity.Get(8) + inverseMass);

	//deltaVelocity.InvMatrix();
	Matrix impulseMatrix = deltaVelocity.InvMatrix();
	//impulseMatrix.InvMatrix();
	//deltaVelocity.InvMatrix();

	Vector3D velKill(m_DesiredDeltaVelocity, -m_ContactVelocity.Y, -m_ContactVelocity.Z);

	impulseContact = impulseMatrix.Transform(velKill);

	float planarImpulse = sqrt(impulseContact.Y * impulseContact.Y + impulseContact.Z + impulseContact.Z);


	if (planarImpulse > impulseContact.X * m_Friction)
	{
		impulseContact.Y /= planarImpulse;
		impulseContact.Z /= planarImpulse;

		impulseContact.X = deltaVelocity.Get(0) + deltaVelocity.Get(1) * m_Friction * impulseContact.Y + deltaVelocity.Get(2) * m_Friction * impulseContact.Z;
		impulseContact.Y *= m_Friction * impulseContact.X;
		impulseContact.Z *= m_Friction * impulseContact.X;
	}

	return impulseContact;
}