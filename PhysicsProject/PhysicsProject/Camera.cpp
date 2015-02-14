//======================================================================
//File: Camera.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Handles translations and rotations for viewing
//======================================================================
#define _USE_MATH_DEFINES

#include "Camera.h"
#include <gl\glut.h>
#include <math.h>
#include <iostream>

using namespace std;

//--------------------------------------------------------------------------------
Camera::Camera()
{
	m_Position = Vector3D(0, 0, 0);
	m_LastMousePosition = Vector3D(0, 0, 0);
	m_Rotation = Vector3D(0, 0, 0);
	m_MouseSpeed = 0.0f;
	m_CameraSpeed =  0.0f;
	m_Move_Up = false;
	m_Move_Down = false;
	m_Move_Left = false;
	m_Move_Right = false;
	m_Move_Foward = false;
	m_Move_Back = false;
	m_IsFollowing = false;
	m_CurrentFollowIndex = 0;
}

//--------------------------------------------------------------------------------
Camera::~Camera()
{
}

//--------------------------------------------------------------------------------
void Camera::Initalize(Vector3D screenSize, std::vector<Planet*> planets, float followDistane)
{
	m_ScreenSize = screenSize;
	m_Position = Vector3D(-1, 1, 1);
	m_LastMousePosition = Vector3D(0, 0, 0);
	m_Rotation = Vector3D(0, 0, 0);
	m_MouseSpeed = 1.0f / 10.0f;
	m_CameraSpeed = 1.0f / 10.0f;

	m_Move_Up = false;
	m_Move_Down = false;
	m_Move_Left = false;
	m_Move_Right = false;
	m_Move_Foward = false;
	m_Move_Back = false;

	m_IsFollowing = false;
	m_IsZoomedOut = true;
	m_CurrentFollowIndex = 0;
	m_Planets = planets;
	m_FollowDistance = followDistane;
}

void Camera::UpdateScreenSize(Vector3D screenSize)
{
	m_ScreenSize = screenSize;
}

//--------------------------------------------------------------------------------
void Camera::HandleMouse(Vector3D mousePosition)
{
	Vector3D difference = mousePosition - m_LastMousePosition;
	m_LastMousePosition = mousePosition;
	m_Rotation.X = m_Rotation.X + difference.Y * m_MouseSpeed;
	m_Rotation.Y = m_Rotation.Y + difference.X * m_MouseSpeed;
}

//--------------------------------------------------------------------------------
void Camera::move()
{
	Vector3D radianRotation = Vector3D(0, 0, 0);
	radianRotation.X = (float)(m_Rotation.X / 180 * M_PI);
	radianRotation.Y = (float)(m_Rotation.Y / 180 * M_PI);
	
	if (m_Move_Foward && !m_Move_Back)
	{
		m_Position.X += float(sin(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Z -= float(cos(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Y -= float(sin(radianRotation.X)) * m_CameraSpeed;
	}

	if (!m_Move_Foward && m_Move_Back)
	{
		m_Position.X -= float(sin(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Z += float(cos(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Y += float(sin(radianRotation.X)) * m_CameraSpeed;
	}

	if (!m_Move_Left && m_Move_Right)
	{
		m_Position.X += float(cos(radianRotation.Y)) * 0.1f;
		m_Position.Z += float(sin(radianRotation.Y)) * 0.1f;
	}

	if (m_Move_Left && !m_Move_Right)
	{
		m_Position.X -= float(cos(radianRotation.Y)) * 0.1f;
		m_Position.Z -= float(sin(radianRotation.Y)) * 0.1f;
	}

	if (m_Move_Up && !m_Move_Down)
	{
		m_Position.Y -= float(sin(radianRotation.X)) * m_CameraSpeed;
	}

	if (!m_Move_Up && m_Move_Down)
	{
		m_Position.Y += float(sin(radianRotation.X)) * m_CameraSpeed;
	}
}

//--------------------------------------------------------------------------------
void Camera::HandleKeyPressed(unsigned char key)
{
	switch (key)
	{
	case '0':
		//reset
		m_IsZoomedOut = true;
		m_IsFollowing = false;
		break;
	case '1':
		m_CurrentFollowIndex = 0;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '2':
		m_CurrentFollowIndex = 1;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '3':
		m_CurrentFollowIndex = 2;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '4':
		m_CurrentFollowIndex = 3;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '5':
		m_CurrentFollowIndex = 4;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '6':
		m_CurrentFollowIndex = 5;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '7':
		m_CurrentFollowIndex = 6;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '8':
		m_CurrentFollowIndex = 7;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case '9':
		m_CurrentFollowIndex = 8;
		m_IsFollowing = true;
		m_IsZoomedOut = false;
		break;
	case 'w':
		m_Move_Foward = true;
		m_IsFollowing = false;
		m_IsZoomedOut = false;
		break;
	case 's':
		m_Move_Back = true;
		m_IsFollowing = false;
		m_IsZoomedOut = false;
		break;
	case 'd':
		m_Move_Right = true;
		m_IsFollowing = false;
		m_IsZoomedOut = false;
		break;
	case 'a':
		m_Move_Left = true;
		m_IsFollowing = false;
		m_IsZoomedOut = false;
		break;
	case 'q':
		m_Move_Up = true;
		m_IsFollowing = false;
		m_IsZoomedOut = false;
		break;
	case 'e':
		m_Move_Down = true;
		m_IsFollowing = false;
		m_IsZoomedOut = false;
		break;
	}
}


//--------------------------------------------------------------------------------
void Camera::HandleKeyReleased(unsigned char key)
{
	switch (key)
	{
	case 'w':
		m_Move_Foward = false;
		break;
	case 's':
		m_Move_Back = false;
		break;
	case 'd':
		m_Move_Right = false;
		break;
	case 'a':
		m_Move_Left = false;
		break;
	case 'q':
		m_Move_Up = false;
		break;
	case 'e':
		m_Move_Down = false;
		break;
	}
}

void Camera::Update()
{
	if (m_IsFollowing)
	{
		m_Position = m_Planets[m_CurrentFollowIndex]->GetPosition();
		m_Rotation = Vector3D(90.0f, 0.0f, 0.0f);
		m_Position.Y += m_FollowDistance;
	}
	else if (m_IsZoomedOut)
	{
		m_Position = Vector3D(0.0f, m_FollowDistance * 10.0f, 0.0f);
		m_Rotation = Vector3D(90.0f, 0.0f, 0.0f);
	}
	else
	{
		move();
	}
	

	glLoadIdentity();
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	glTranslated(-m_Position.X, -m_Position.Y, -m_Position.Z);
	m_LastMousePosition = Vector3D((float)((int)((m_ScreenSize.X / 2.0f))),
		(float)((int)((m_ScreenSize.Y / 2.0f))), 0);
}
//======================================================================