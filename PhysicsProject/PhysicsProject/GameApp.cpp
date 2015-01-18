//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2915
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
void GameApp::Init()
{
	mp_Camera = new Camera();
}

//--------------------------------------------------------------------------------
void GameApp::Update()
{
	mp_Camera->Update();
}

//--------------------------------------------------------------------------------
void GameApp::HandleMouse(Vector3D mousePos)
{
	mp_Camera->HandleMouse(mousePos);
}

void GameApp::HandleKey(unsigned char key)
{
	mp_Camera->HandleKey(key);
}

//--------------------------------------------------------------------------------
void GameApp::CleanUp()
{
	delete mp_Camera;
	mp_Camera = nullptr;
}
//================================================================================