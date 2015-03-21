//======================================================================
//File: GameApp.h
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Holds Game State Information
//======================================================================
#ifndef GAMEAPP_H
#define GAMEAPP_H
//======================================================================
#include "Camera.h"
#include "Level.h"
#include "Vector3D.h"
#include "EditorState.h"
#include "PlanetSystem.h"
#include "PhysicsObjectSystem.h"
#include "GravityGenerator.h"
#include "EarthGravityGenerator.h"
#include "GL\glui.h"
class Skybox;
//======================================================================
class GameApp
{
public:
	GameApp();
	~GameApp();

	static int TimeStep;
	static bool DebugData;

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
	PhysicsObjectSystem* mp_PhysicsObjectSystem;
	Skybox* mp_SkyBox;
	Level* m_Level;
};
#endif
//================================================================================