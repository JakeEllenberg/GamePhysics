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

}

//--------------------------------------------------------------------------------
void GameApp::Init(Vector3D screenSize)
{
	mp_Camera = new Camera();
	mp_Camera->Initalize(screenSize); 
	m_PhysicsObject = new PhysicsObject();
	m_PhysicsObject->Inititalize(Vector3D(0,0,0), Vector3D(0.0f, 0.0f, 0.0f));
	m_FireworkLauncher = new FireworkLauncher();
	m_FireworkLauncher->Initialzie(Vector3D::Zero, Vector3D(0.0, 0.01f, 0.0f), 1000, 1, 10, 500, 1500, 10, 0.01f, 0.1f, 100, 10);
}

void GameApp::UpdateScreenSize(Vector3D screenSize)
{
	mp_Camera->UpdateScreenSize(screenSize);
}

//--------------------------------------------------------------------------------
void GameApp::Update(int deltaTime, const EditorState* state)
{
	if (!state->GetIsPaused())
	{
		update(deltaTime);
	}
	mp_Camera->Update();
}

//--------------------------------------------------------------------------------
void GameApp::update(int deltaTime)
{	
	m_PhysicsObject->Update(deltaTime);
	m_FireworkLauncher->Update(deltaTime);
}

//--------------------------------------------------------------------------------
void GameApp::Draw()
{
	//m_PhysicsObject->Draw();
	m_FireworkLauncher->Draw();
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
	m_PhysicsObject->Reset();
	m_FireworkLauncher->Reset();
}

//--------------------------------------------------------------------------------
void GameApp::CleanUp()
{
	delete mp_Camera;
	mp_Camera = nullptr;

	if (m_FireworkLauncher != nullptr)
	{
		m_FireworkLauncher->CleanUp();
	}
	delete m_FireworkLauncher;
	m_FireworkLauncher = nullptr;
}
//================================================================================