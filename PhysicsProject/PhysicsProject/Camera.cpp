//======================================================================
//File: Camera.cpp
//Author: Jake Ellenberg
//Created: 1/17/2915
//Purpose: Handles translations and rotations for viewing
//======================================================================
#define _USE_MATH_DEFINES

#include "Camera.h"
#include <gl\glut.h>
#include <math.h>


//--------------------------------------------------------------------------------
Camera::Camera()
{
	m_Position = Vector3D(0, 0, 0);
	m_LastMousePosition = Vector3D(0, 0, 0);
	m_Rotation = Vector3D(0, 0, 0);
	m_MouseSpeed = 1.0f / 10.0f;
	m_CameraSpeed =  1.0f / 2.0f;
}

//--------------------------------------------------------------------------------
Camera::~Camera()
{
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
void Camera::HandleKey(unsigned char key)
{
	Vector3D radianRotation = Vector3D(0, 0, 0);
	if (key == 'w')
	{
		radianRotation.Y = (float)(m_Rotation.Y / 180 * M_PI);
		radianRotation.X = (float)(m_Rotation.X / 180 * M_PI);
		m_Position.X += float(sin(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Z -= float(cos(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Y -= float(sin(radianRotation.X)) * m_CameraSpeed;
	}

	if (key == 's')
	{
		radianRotation.Y = (float)(m_Rotation.Y / 180 * M_PI);
		radianRotation.X = (float)(m_Rotation.X / 180 * M_PI);
		m_Position.X -= float(sin(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Z += float(cos(radianRotation.Y)) * m_CameraSpeed;
		m_Position.Y += float(sin(radianRotation.X)) * m_CameraSpeed;
	}

	if (key == 'd')
	{
		radianRotation.Y = (float)(m_Rotation.Y / 180.0f * M_PI);
		m_Position.X += float(cos(radianRotation.Y)) * 0.1f;
		m_Position.Z += float(sin(radianRotation.Y)) * 0.1f;
	}

	if (key == 'a')
	{
		radianRotation.Y = (float)(m_Rotation.Y / 180.0f * M_PI);
		m_Position.X -= float(cos(radianRotation.Y)) * 0.1f;
		m_Position.Z -= float(sin(radianRotation.Y)) * 0.1f;
	}
}

void Camera::Update()
{
	glLoadIdentity();
	glRotatef(m_Rotation.X, 1.0, 0.0, 0.0);
	glRotatef(m_Rotation.Y, 0.0, 1.0, 0.0);
	glTranslated(-m_Position.X, -m_Position.Y, -m_Position.Z);
}
//======================================================================