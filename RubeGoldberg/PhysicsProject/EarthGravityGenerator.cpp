#include "EarthGravityGenerator.h"


EarthGravityGenerator::EarthGravityGenerator(Vector3D gravity)
{
	m_Gravity = gravity;
	m_Type = GeneratorType::EARTH_GRAVITY_GENERATOR;
}


EarthGravityGenerator::~EarthGravityGenerator()
{

}

void EarthGravityGenerator::UpdateForce(PhysicsObject* object)
{
	object->AddForce(m_Gravity * object->GetMass());
}
