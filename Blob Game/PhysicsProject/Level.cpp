//======================================================================
//File: Level.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Hold level data
//======================================================================
#include "Level.h"
#include "RodContactGenerator.h"

//--------------------------------------------------------------------------------
Level::Level()
{
}

//--------------------------------------------------------------------------------
Level::~Level()
{
	CleanUp();
}

//--------------------------------------------------------------------------------
void Level::Initialize()
{
	m_Ground = new Ground();
	m_Ground->Inititalize("Seige/siege_bot.jpg");
	m_Player = new Player();
	m_Player->Inititalize(1.0f, Vector3D(0,5,0), Vector3D(0,0,0), Vector3D::Zero, Vector3D::Zero, 1.0f, "Characters/smile-texture.jpg");
	m_Player->SetDampening(0.9999f);

	RenderObject* collectable1 = new RenderObject();
	collectable1->Inititalize(1.0f, Vector3D(5, 5, 0), Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, 1.0f, "Characters/smile-texture2.jpg");
	collectable1->SetDampening(0.999f);

	RenderObject* collectable2 = new RenderObject();
	collectable2->Inititalize(1.0f, Vector3D(10, 5, 0), Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, 1.0f, "Characters/smile-texture2.jpg");
	collectable2->SetDampening(0.999f);
	
	m_RenderObjects.push_back(collectable1);
	m_RenderObjects.push_back(collectable2);

	m_ContactGenerators.push_back(new RodContactGenerator(collectable1, collectable2, 10.0f));
}

//--------------------------------------------------------------------------------
void Level::Draw()
{
	for (unsigned int i = 0; i < m_RenderObjects.size(); i++)
	{
		m_RenderObjects[i]->Draw();
	}
	m_Ground->Draw();
	m_Player->Draw();
}
std::vector<PhysicsObject*> Level::GetCollisionObjects()
{
	std::vector<PhysicsObject*> collisionObjects;
	collisionObjects.push_back(m_Player);

	for each(RenderObject* object in m_RenderObjects)
	{
		collisionObjects.push_back(object);
	}

	return collisionObjects;
}

std::vector<ContactGenerator*> Level::GetContactGenerators()
{
	return m_ContactGenerators;
}

//--------------------------------------------------------------------------------
void Level::CleanUp()
{
	delete m_Ground;
	m_Ground = nullptr;
	delete m_Player;
	m_Player = new Player();
	for (unsigned int i = 0; i < m_RenderObjects.size(); i++)
	{
		delete m_RenderObjects[i];
	}
	m_RenderObjects.clear();
	m_ContactGenerators.clear();
}