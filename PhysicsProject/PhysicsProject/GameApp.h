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
#include "PlanetSystem.h"
#include "PhysicsObjectSystem.h"
#include "GravityGenerator.h"
class Skybox;
//======================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();

	static int TimeStep;

	void Init(Vector3D screenSize);
	void Update(float deltaTime, const EditorState* state);
	void CleanUp();
	void HandleMouse(Vector3D mousePos);
	void HandleKeyPressed(unsigned char key);
	void HandleKeyReleased(unsigned char key);
	void UpdateScreenSize(Vector3D screenSize);
	void Draw();
	void Reset();
private:
	Camera* mp_Camera;
	void update(float deltaTime);
	PlanetSystem* mp_PlanetSystem;
	PhysicsObjectSystem* mp_PhysicsObjectSystem;
	Skybox* mp_SkyBox;
};
#endif
//================================================================================