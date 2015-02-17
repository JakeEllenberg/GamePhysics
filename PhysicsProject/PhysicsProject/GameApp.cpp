//======================================================================
//File: Main.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Entry point of the program, setup OpenGl functionality.
//======================================================================
#include "Skybox.h"
#include "GameApp.h"
//================================================================================
int GameApp::TimeStep = 50;
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

	mp_SkyBox = new Skybox();
	mp_SkyBox->Initialize();
	
	mp_PlanetSystem = new PlanetSystem();
	mp_PlanetSystem->Initialize();
	mp_PhysicsObjectSystem = new PhysicsObjectSystem();
	mp_PhysicsObjectSystem->Initialize();
	GravityGenerator* gravityGenerator = new GravityGenerator();
	mp_PhysicsObjectSystem->Add(gravityGenerator);

	std::vector<Planet*> planets = mp_PlanetSystem->GetPlanets();
	std::vector<PhysicsObject*> planetsAsPhysicsObjects;

	mp_Camera->Initalize(screenSize, planets, 2.5f);

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
	
	Planet* currentPlanet = mp_PlanetSystem->GetPlanets()[m_CurrentSelectIndex];
	std::string planetName = "Planet Name: " + currentPlanet->GetName();
	mp_GluiText_Name->set_text(planetName.c_str());

	std::string planetMass = std::to_string(currentPlanet->GetMass() * 1.9891 *  pow(10, 30));
	planetMass = planetMass.substr(0, planetMass.size() - 5); // take off all but the first decimal point
	mp_GluiText_Mass->set_text(planetMass.c_str());

	std::string planetPosition = "Position(KM): " + (currentPlanet->GetPosition() * 149597871.0f).ToString(true);
	mp_GluiText_Position->set_text(planetPosition.c_str());

	std::string planetVelocity = "Velocity(KM/S): " + (currentPlanet->GetVelocity() * 149597871.0f).ToString();
	mp_GluiText_Velocity->set_text(planetVelocity.c_str());

	std::string planetAcceleration = "Acceleration(M/(S*S)): " + (currentPlanet->GetAcceleration() * 149597871.0f * 1000).ToString();
	mp_GluiText_Acceleration->set_text(planetAcceleration.c_str());
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
	mp_PhysicsObjectSystem->Draw();
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
	switch (key)
	{
	case '1':
		m_CurrentSelectIndex = 1;
		break;
	case '2':
		m_CurrentSelectIndex = 2;
		break;
	case '3':
		m_CurrentSelectIndex = 3;
		break;
	case '4':
		m_CurrentSelectIndex = 4;
		break;
	case '5':
		m_CurrentSelectIndex = 5;
		break;
	case '6':
		m_CurrentSelectIndex = 6;
		break;
	case '7':
		m_CurrentSelectIndex = 7;
		break;
	case '8':
		m_CurrentSelectIndex = 8;
		break;
	case '9':
		m_CurrentSelectIndex = 9;
		break;
	}
	mp_Camera->HandleKeyPressed(key);
	mp_Camera->SetCurrentFollowIndex(m_CurrentSelectIndex);
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