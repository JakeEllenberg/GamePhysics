//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2915
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

	void Init();
	void Update();
	void CleanUp();
	void HandleMouse(Vector3D mousePos);
	void HandleKey(unsigned char key);
private:
	Camera* mp_Camera;
};
#endif
//================================================================================