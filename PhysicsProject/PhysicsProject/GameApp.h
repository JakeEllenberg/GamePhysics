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
	inline void SetGluiText(GLUI_StaticText* name, GLUI_StaticText* mass, GLUI_StaticText* position, GLUI_StaticText* velocity, GLUI_StaticText* acceleration) 
	{
		mp_GluiText_Name = name; mp_GluiText_Mass = mass; mp_GluiText_Position = position; mp_GluiText_Velocity = velocity; mp_GluiText_Acceleration = acceleration;
	};

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
	int m_CurrentSelectIndex;

	GLUI_StaticText* mp_GluiText_Name;
	GLUI_StaticText* mp_GluiText_Mass;
	GLUI_StaticText* mp_GluiText_Position;
	GLUI_StaticText* mp_GluiText_Velocity;
	GLUI_StaticText* mp_GluiText_Acceleration;
	
};
#endif
//================================================================================