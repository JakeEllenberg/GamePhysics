//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Entry point of the program, setup OpenGl functionality.
//======================================================================
#include "GameApp.h"

//================================================================================
GameApp::GameApp()
{
	mp_Camera = nullptr;
}

//--------------------------------------------------------------------------------
GameApp::~GameApp()
{
	CleanUp();
}

//--------------------------------------------------------------------------------
void GameApp::Init(Vector3D screenSize)
{
	mp_Camera = new Camera();
	mp_Camera->Initalize(screenSize); 
	mp_PlanetSystem = new PlanetSystem();
	mp_PlanetSystem->Initialize();
	mp_PhysicsObjectSystem = new PhysicsObjectSystem();
	mp_PhysicsObjectSystem->Initialize();
	GravityGenerator* gravityGenerator = new GravityGenerator();
	mp_PhysicsObjectSystem->Add(gravityGenerator);

	std::vector<Planet*> planets = mp_PlanetSystem->GetPlanets();
	std::vector<PhysicsObject*> planetsAsPhysicsObjects;
	for (unsigned int i = 0; i < planets.size(); i++)
	{
		mp_PhysicsObjectSystem->Add(planets[i]);
		planetsAsPhysicsObjects.push_back(planets[i]);
	}
	mp_PhysicsObjectSystem->AddToRegistry(planetsAsPhysicsObjects, GeneratorType::GRAVITY_GENERATOR);
}

void GameApp::UpdateScreenSize(Vector3D screenSize)
{
	mp_Camera->UpdateScreenSize(screenSize);
}

//--------------------------------------------------------------------------------
void GameApp::Update(float deltaTime, const EditorState* state)
{
	if (!state->GetIsPaused())
	{
		update(deltaTime);
	}
	mp_Camera->Update();
}

//--------------------------------------------------------------------------------
void GameApp::update(float deltaTime)
{
	mp_PhysicsObjectSystem->Update(deltaTime);
}

//--------------------------------------------------------------------------------
void GameApp::Draw()
{
	mp_PhysicsObjectSystem->Draw();
}

//--------------------------------------------------------------------------------
void GameApp::HandleMouse(Vector3D mousePos)
{
	mp_Camera->HandleMouse(mousePos);
}

//--------------------------------------------------------------------------------
void GameApp::HandleKeyPressed(unsigned char key)
{
	mp_Camera->HandleKeyPressed(key);
}

//--------------------------------------------------------------------------------
void GameApp::HandleKeyReleased(unsigned char key)
{
	mp_Camera->HandleKeyReleased(key);
}

//--------------------------------------------------------------------------------
void GameApp::Reset()
{
	mp_PhysicsObjectSystem->Reset();
}

//--------------------------------------------------------------------------------
void GameApp::CleanUp()
{
	delete mp_Camera;
	mp_Camera = nullptr;
}
//================================================================================