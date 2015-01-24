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
#include "EditorState.h"
#include "PhysicsObject.h"
#include "FireworkLauncher.h"
//======================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();

	void Init(Vector3D screenSize);
	void Update(int deltaTime, const EditorState* state);
	void CleanUp();
	void HandleMouse(Vector3D mousePos);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
	void UpdateScreenSize(Vector3D screenSize);
	void Draw();
	void Reset();
private:
	Camera* mp_Camera;
	void update(int deltaTime);
	PhysicsObject* m_PhysicsObject;
	FireworkLauncher* m_FireworkLauncher;
};
#endif
//================================================================================