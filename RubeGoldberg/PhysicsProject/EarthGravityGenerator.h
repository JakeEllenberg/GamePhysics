#pragma once
#include "ForceGenerator.h"
class EarthGravityGenerator :
	public ForceGenerator
{
public:
	EarthGravityGenerator(Vector3D gravity);
	~EarthGravityGenerator();

	virtual void UpdateForce(PhysicsObject* object);
private:
	Vector3D m_Gravity;
};

