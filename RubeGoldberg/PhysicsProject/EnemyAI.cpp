#include "EnemyAI.h"


EnemyAI::EnemyAI(Player* player, Shape* shape, float speed)
{
	m_Player = player;
	m_Shape = shape;
	m_PlayerAttached = false;
	m_PlayerDetected = false;
	m_Speed = speed;
}


EnemyAI::~EnemyAI()
{
}

void EnemyAI::Update()
{
	if (m_PlayerDetected)
	{
		for each(PhysicsObject* physicsObject in m_Shape->GetPhysicsObjects())
		{
			Vector3D direction = m_Player->GetPosition() - physicsObject->GetPosition();
			direction.Y = 0;
			direction.Normalize();
			if (m_PlayerAttached && m_Shape->GetPhysicsObjects()[0]->GetPosition().Magnitude() < 35)
			{
				direction = direction * -1;
			}
			
			physicsObject->AddForce(direction * m_Speed);
		}
	}
	else
	{
		if (GetPlayerDistance() < 10)
		{
			m_PlayerDetected = true;
		}
	}
}
