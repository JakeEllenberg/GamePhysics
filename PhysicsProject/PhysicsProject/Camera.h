//======================================================================
//File: Camera.h
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Handles translations and rotations for viewing
//======================================================================
#ifndef CAMERA_H
#define CAMERA_H
//======================================================================
#include "Vector3D.h"
#include <vector>
#include "Planet.h"
//======================================================================
class Camera
{
public:
	Camera();
	~Camera();
	void Initalize(Vector3D screenSize, std::vector<Planet*> planets, float followDistance);
	void UpdateScreenSize(Vector3D screenSize);
	void HandleMouse(Vector3D mousePos);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
	void Update();
private:
	void move();
private:
	Vector3D m_LastMousePosition;
	Vector3D m_Rotation;
	Vector3D m_Position;
	Vector3D m_ScreenSize;

	bool m_Move_Foward;
	bool m_Move_Back;
	bool m_Move_Left;
	bool m_Move_Right;
	bool m_Move_Up;
	bool m_Move_Down;

	float m_MouseSpeed;
	float m_CameraSpeed;

	int m_CurrentFollowIndex;
	bool m_IsFollowing;
	bool m_IsZoomedOut;
	float m_FollowDistance;
	std::vector<Planet*> m_Planets;
};
#endif
//======================================================================