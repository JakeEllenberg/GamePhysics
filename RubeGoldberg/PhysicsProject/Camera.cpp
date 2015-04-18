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
	m_CameraObject = nullptr;
}

//--------------------------------------------------------------------------------
Camera::~Camera()
{
	delete m_CameraObject;
	m_CameraObject = nullptr;
}

//--------------------------------------------------------------------------------
void Camera::Initalize(Vector3D screenSize, PhysicsObject* cameraObject)
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

	m_CameraObject = cameraObject;
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
		case 'w':
			m_Move_Foward = true;
			break;
		case 's':
			m_Move_Back = true;
			break;
		case 'd':
			m_Move_Right = true;
			break;
		case 'a':
			m_Move_Left = true;
			break;
		case 'q':
			m_Move_Up = true;
			break;
		case 'e':
			m_Move_Down = true;
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

//--------------------------------------------------------------------------------
void Camera::Update()
{
	move();
 	glLoadIdentity();
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	//glTranslated(-m_Position.X, -m_Position.Y, -m_Position.Z);
	glTranslated(-m_CameraObject->GetPosition().X, -10.0f, -m_CameraObject->GetPosition().Z);
	m_LastMousePosition = Vector3D((float)((int)((m_ScreenSize.X / 2.0f))),
		(float)((int)((m_ScreenSize.Y / 2.0f))), 0);
}
//======================================================================