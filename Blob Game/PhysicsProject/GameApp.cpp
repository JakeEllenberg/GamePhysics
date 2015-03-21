//======================================================================
//File: GameApp.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Holds Game State Information
//======================================================================
#include "Skybox.h"
#include "GameApp.h"
//================================================================================
int GameApp::TimeStep = 1;
bool GameApp::DebugData = false;
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

	mp_SkyBox = new Skybox();
	mp_SkyBox->Initialize();

	m_Level = new Level();
	m_Level->Initialize();

	EarthGravityGenerator* earthGravity = new EarthGravityGenerator(Vector3D(0, -9.8f, 0));

	std::vector<PhysicsObject*> collisionObjects = m_Level->GetCollisionObjects();
	
	mp_PhysicsObjectSystem = new PhysicsObjectSystem();
	mp_PhysicsObjectSystem->Initialize();
	mp_PhysicsObjectSystem->Add(earthGravity);

	for each (PhysicsObject* object in collisionObjects)
	{
		mp_PhysicsObjectSystem->Add(object);
	}
	mp_PhysicsObjectSystem->AddToRegistry(collisionObjects, GeneratorType::EARTH_GRAVITY_GENERATOR);
	
	std::vector<ContactGenerator*> contactGenerators = m_Level->GetContactGenerators();

	for each(ContactGenerator* contactGenerator in contactGenerators)
	{
		mp_PhysicsObjectSystem->Add(contactGenerator);
	}

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
	bool tempDebugData = DebugData;
	DebugData = false;
	for (int i = 0; i < TimeStep - 1; i++) //-1 for the debug update
	{
		mp_PhysicsObjectSystem->Update(deltaTime);
	}
	DebugData = tempDebugData;
	mp_PhysicsObjectSystem->Update(deltaTime); //call the last one with the debug info
}

//--------------------------------------------------------------------------------
void GameApp::Draw()
{
	m_Level->Draw();
	mp_SkyBox->Render();
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