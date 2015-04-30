#include "RigidBox.h"


RigidBox::RigidBox()
{
	m_RigidType = RigidType::BOX;
}


RigidBox::~RigidBox()
{
}

void RigidBox::Inititalize(std::string imageName, float size, float mass, Vector3D initialPosition)
{
	RigidRender::Inititalize(imageName, mass, initialPosition);
	m_Size = size;
	m_RigidType = RigidType::BOX;
}

void RigidBox::drawObject()
{
	glTranslatef(m_Position.X, m_Position.Y, m_Position.Z);
	float magnitude = m_Rotation.Magnitude();
	Vector3D direction = m_Rotation.Normalized();
	glRotatef(magnitude, direction.X, direction.Y, direction.Z);
	glutSolidCube(m_Size);
}