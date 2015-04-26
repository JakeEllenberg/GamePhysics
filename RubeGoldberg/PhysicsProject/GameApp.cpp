//======================================================================
//File: GameApp.cpp
//Author: Jake Ellenberg
//Created: 1/17/2015
//Purpose: Holds Game State Information
//======================================================================
#include "Skybox.h"
#include "GameApp.h"
#include "SpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "CableContactGenerator.h"
#include <map>
#include "ImageHandler.h"
//================================================================================
int GameApp::TimeStep = 1;
bool GameApp::DebugData = false;
//================================================================================
GameApp::GameApp()
{
	mp_Camera = nullptr;
	m_LoadedTextures = false;
}

//--------------------------------------------------------------------------------
GameApp::~GameApp()
{
	CleanUp();
}

//--------------------------------------------------------------------------------
void GameApp::Init(Vector3D screenSize)
{
	if (!m_LoadedTextures)
	{
		ImageHandler::GetInstance()->AddImage("Seige/siege_right.jpg", "Sky_right");
		ImageHandler::GetInstance()->AddImage("Seige/siege_left.jpg", "Sky_left");
		ImageHandler::GetInstance()->AddImage("Seige/siege_top.jpg", "Sky_top");
		ImageHandler::GetInstance()->AddImage("Seige/siege_front.jpg", "Sky_front");
		ImageHandler::GetInstance()->AddImage("Seige/siege_bot.jpg", "Sky_bot");
		ImageHandler::GetInstance()->AddImage("Seige/siege_back.jpg", "Sky_bck");
		ImageHandler::GetInstance()->AddImage("Characters/smile-texture.jpg", "Smile1");
		ImageHandler::GetInstance()->AddImage("Characters/smile-texture2.jpg", "Smile2");
		ImageHandler::GetInstance()->AddImage("Characters/smile-texture3.jpg", "Smile3");
		ImageHandler::GetInstance()->AddImage("Characters/smile-texture4.jpg", "Smile4");
		ImageHandler::GetInstance()->AddImage("Characters/smile-texture5.jpg", "Smile5");
		m_LoadedTextures = true;
	}
	

	m_ScreenSize = screenSize;
	Vector3D cameraOffSet = Vector3D(0, 0, 10);
	PhysicsObject* cameraObject = new PhysicsObject();
	

	mp_Camera = new Camera();
	mp_Camera->Initalize(screenSize, cameraObject);

	mp_SkyBox = new Skybox();
	mp_SkyBox->Initialize();

	m_Level = new Level();
	m_Level->Initialize();
	cameraObject->Inititalize(1.0f, m_Level->GetPlayer()->GetPosition() + cameraOffSet);
	cameraObject->SetDampening(.9f);

	EarthGravityGenerator* earthGravity = new EarthGravityGenerator(Vector3D(0, -9.8f, 0));

	std::vector<PhysicsObject*> collisionObjects = m_Level->GetCollisionObjects();
	
	mp_PhysicsObjectSystem = new PhysicsObjectSystem();
	mp_PhysicsObjectSystem->Initialize();
	mp_PhysicsObjectSystem->Add(earthGravity);

	for each(RigidRender* rigidRender in m_Level->GetRigidRenders())
	{
		RigidBody* body = (RigidBody*)rigidRender;
		mp_PhysicsObjectSystem->Add(body);
		mp_PhysicsObjectSystem->AddToRegistry(earthGravity, body);
	}

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

	std::map<SpringForceGenerator*, std::vector<PhysicsObject*>> springForceGenerators = m_Level->GetSpringForceGenerators();

	std::map<SpringForceGenerator*, std::vector<PhysicsObject*>>::iterator iter;
	for (iter = springForceGenerators.begin(); iter != springForceGenerators.end(); iter++)
	{
		for each(PhysicsObject* physicsObject in iter->second)
		{
			mp_PhysicsObjectSystem->AddToRegistry(physicsObject, iter->first);
		}
	}

	mp_PhysicsObjectSystem->Add(cameraObject);
	mp_PhysicsObjectSystem->AddToRegistry(cameraObject, new BungeeForceGenerator(10.0f, 10.0f, m_Level->GetPlayer()));

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
	m_Level->UpdateAI();
	std::vector<Shape*> collidingCollectables = m_Level->GetCollidingCollectables();
	for each(Shape* shape in collidingCollectables)
	{
		CableContactGenerator* cable = new CableContactGenerator(m_Level->GetPlayer(), shape->GetPhysicsObjects()[0],
			m_Level->GetPlayer()->GetPosition().CalculateDistance(shape->GetPhysicsObjects()[0]->GetPosition()));
		mp_PhysicsObjectSystem->Add(cable);
	}
	std::vector<EnemyAI*> enemies = m_Level->GetCollidingEnemies();
	for each(EnemyAI* enemy in enemies)
	{
		mp_PhysicsObjectSystem->AddToRegistry(m_Level->GetPlayer(), new SpringForceGenerator(10.0f, 4.0f, enemy->GetShape()->GetPhysicsObjects()[0]));
		enemy->SetPlayerAttached();
	}

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
	m_Level->GetPlayer()->HandleKeyPressed(key);
	
}

//--------------------------------------------------------------------------------
void GameApp::HandleKeyReleased(unsigned char key)
{
	mp_Camera->HandleKeyReleased(key);
	m_Level->GetPlayer()->HandleKeyReleased(key);
}

//--------------------------------------------------------------------------------
void GameApp::Reset()
{
	//mp_PhysicsObjectSystem->Reset();
	CleanUp();
	Init(m_ScreenSize);
}

//--------------------------------------------------------------------------------
void GameApp::CleanUp()
{
	if (mp_PhysicsObjectSystem != nullptr)
	{
		mp_PhysicsObjectSystem->CleanUp();
	}
	delete mp_PhysicsObjectSystem;
	mp_PhysicsObjectSystem = nullptr;
	if (m_Level != nullptr)
	{
		m_Level->CleanUp();
	}
	delete m_Level;
	m_Level = nullptr;
	delete mp_Camera;
	mp_Camera = nullptr;
}
//================================================================================