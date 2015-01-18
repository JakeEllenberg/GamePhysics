//======================================================================
//File: Camera.h
//Author: Jake Ellenberg
//Created: 1/17/2915
//Purpose: Handles translations and rotations for viewing
//======================================================================
#ifndef CAMERA_H
#define CAMERA_H
//======================================================================
#include "Vector3D.h"
//======================================================================
class Camera
{
public:
	Camera();
	~Camera();
	void HandleMouse(Vector3D mousePos);
	void HandleKey(unsigned char key);
	void Update();
private:
	Vector3D m_LastMousePosition;
	Vector3D m_Rotation;
	Vector3D m_Position;

	float m_MouseSpeed;
	float m_CameraSpeed;
};
#endif
//======================================================================