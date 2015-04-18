//======================================================================
//File: GroundContactGenerator.h
//Author: Jake Ellenberg
//Created: 3/31/2015
//======================================================================
#ifndef ENEMY_AI
#define ENEMY_AI
//======================================================================
#include "Shape.h"
#include "Player.h"
//======================================================================
class EnemyAI
{
public:
	EnemyAI(Player* player, Shape* shape, float speed);
	~EnemyAI();

	inline bool CheckPlayerAttached() { return m_PlayerAttached; };
	inline void SetPlayerAttached() { m_PlayerAttached = true; };
	inline void SetPlayerDetected() { m_PlayerDetected = true; };

	inline float GetPlayerDistance() { return m_Player->GetPosition().CalculateDistance(m_Shape->GetRenderObjects()[0]->GetPosition()); };
	inline Shape* GetShape(){ return m_Shape; };

	void Update();
private:
	Player* m_Player;
	Shape* m_Shape;
	float m_Speed;
	bool m_PlayerAttached;
	bool m_PlayerDetected;
};
#endif
//======================================================================