//======================================================================
//File: Player.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#ifndef PLAYER_H
#define PLAYER_H
//======================================================================
#include "RenderObject.h"
#include <vector>
//======================================================================
class Player : public RenderObject
{
public:
	Player();
	~Player();

	inline void SetSpeed(float speed) { m_Speed = speed; };

	void Update(float sTime);

	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);

private:
	float m_Speed;
	bool m_Pressed_W;
	bool m_Pressed_A;
	bool m_Pressed_S;
	bool m_Pressed_D;
};
#endif
//======================================================================