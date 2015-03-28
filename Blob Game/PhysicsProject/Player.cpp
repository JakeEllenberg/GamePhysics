//======================================================================
//File: Player.cpp
//Author: Jake Ellenberg
//Created: 3/21/2015
//======================================================================
#include "Player.h"

//--------------------------------------------------------------------------------
Player::Player()
{
	m_Pressed_W = false;
	m_Pressed_A = false;
	m_Pressed_S = false;
	m_Pressed_D = false;
}

//--------------------------------------------------------------------------------
Player::~Player()
{
}

void Player::Update(float sTime)
{
	if (m_Pressed_W)
	{
		AddForce(Vector3D(0, 0, -m_Speed));
	}
	if (m_Pressed_S)
	{
		AddForce(Vector3D(0, 0, m_Speed));
	}
	if (m_Pressed_D)
	{
		AddForce(Vector3D(-m_Speed, 0, 0));
	}
	if (m_Pressed_A)
	{
		AddForce(Vector3D(m_Speed, 0, 0));
	}

	PhysicsObject::Update(sTime);
}

//--------------------------------------------------------------------------------
void Player::HandleKeyPressed(unsigned char key)
{
	switch (key)
	{
	case 'w':
		m_Pressed_W = true;
		break;
	case 's':
		m_Pressed_S = true;
		break;
	case 'd':
		m_Pressed_A = true;
		break;
	case 'a':
		m_Pressed_D = true;
		break;
	}
}

//--------------------------------------------------------------------------------
void Player::HandleKeyReleased(unsigned char key)
{
	switch (key)
	{
	case 'w':
		m_Pressed_W = false;
		break;
	case 's':
		m_Pressed_S = false;
		break;
	case 'd':
		m_Pressed_A = false;
		break;
	case 'a':
		m_Pressed_D = false;
		break;
	}
}