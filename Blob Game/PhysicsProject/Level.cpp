//======================================================================
//File: Level.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Hold level data
//======================================================================
#include "Level.h"
#include "RodContactGenerator.h"
#include "CableContactGenerator.h"
#include "SpringForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "Cube.h"
#include "Tetrahedron.h"
#include "Pyramid.h"

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
	m_Player->SetSpeed(10.0f);

	RenderObject* collectable1 = new RenderObject();
	collectable1->Inititalize(1.0f, Vector3D(5, 5, 0), Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, 1.0f, "Characters/smile-texture2.jpg");
	collectable1->SetDampening(0.999f);

	RenderObject* collectable2 = new RenderObject();
	collectable2->Inititalize(1.0f, Vector3D(10, 5, 0), Vector3D::Zero, Vector3D::Zero, Vector3D::Zero, 1.0f, "Characters/smile-texture2.jpg");
	collectable2->SetDampening(0.999f);
	
	m_RenderObjects.push_back(collectable1);
	m_RenderObjects.push_back(collectable2);

	Cube* cube = new Cube();
	cube->Inititalize(Vector3D(15, 20, 0), "Characters/smile-texture2.jpg", 10);
	//AddShape(cube);

	Tetrahedron* tet = new Tetrahedron();
	tet->Inititalize(Vector3D(15, 20, 0), "Characters/smile-texture2.jpg", 5);
	//AddShape(tet);

	Pyramid* pyramid = new Pyramid();
	pyramid->Inititalize(Vector3D(15, 20, 0), "Characters/smile-texture2.jpg", 5);
	AddShape(pyramid);


	//m_ContactGenerators.push_back(new CableContactGenerator(collectable1, collectable2, 1.0f));

	//SpringForceGenerator* springOne = new BungeeForceGenerator(1.0f, 2, collectable2);

	//m_SpringForceGenerators[springOne].push_back(collectable1);
}

//--------------------------------------------------------------------------------
void Level::AddShape(Shape* shape)
{
	std::vector<RenderObject*> objects = shape->GetRenderObjects();
	m_RenderObjects.insert(m_RenderObjects.end(), objects.begin(), objects.end());
	std::vector<RodContactGenerator*> rods = shape->GetRods();
	m_ContactGenerators.insert(m_ContactGenerators.end(), rods.begin(), rods.end());
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

std::map<SpringForceGenerator*, std::vector<PhysicsObject*>> Level::GetSpringForceGenerators()
{
	return m_SpringForceGenerators;
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