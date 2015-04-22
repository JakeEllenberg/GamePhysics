#include "CollisionData.h"


CollisionData::CollisionData()
{
	m_Contact = new RigidContact();
}


CollisionData::~CollisionData()
{
	delete m_Contact;
}
