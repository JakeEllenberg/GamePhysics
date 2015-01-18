//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Entry point of the program, setup OpenGl functionality.
//======================================================================
#ifndef GAMEAPP_H
#define GAMEAPP_H
//======================================================================
#include "Camera.h"
#include "Vector3D.h"
//======================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();

	void Init(Vector3D screenSize);
	void Update();
	void CleanUp();
	void HandleMouse(Vector3D mousePos);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
	void UpdateScreenSize(Vector3D screenSize);
private:
	Camera* mp_Camera;
};
#endif
//================================================================================