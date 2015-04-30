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
#include <iostream>
#include <fstream>
#include "ImageHandler.h"
#include "RigidSphere.h"
#include "RigidBox.h"
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
	m_Ground->Inititalize("Sky_bot");
	m_Player = new Player();
	
	

	m_Player->Inititalize(1.0f, Vector3D(0,5,0), Vector3D(0,0,0), Vector3D::Zero, Vector3D::Zero, 1.0f, "Smile1");
	m_Player->SetSpeed(50.0f);
	m_Player->SetDampening(.99f);

	RigidSphere* sphere = new RigidSphere();
	sphere->Inititalize("Smile1", 1.0f, 1.0f, Vector3D(0, 15, 0));

	RigidBox* box = new RigidBox();
	box->Inititalize("Smile2", 1.0f, 1.0f, Vector3D(0, 25, 0));

	RigidSphere* sphere2 = new RigidSphere();
	sphere2->Inititalize("Smile3", 1.0f, 1.0f, Vector3D(0, 10, 0));

	RigidSphere* sphere3 = new RigidSphere();
	sphere3->Inititalize("Smile4", 1.0f, 1.0f, Vector3D(0, 5, 0));
	//sphere2->AddVelocity(Vector3D(6, 0, 0));

	RigidSphere* sphere4 = new RigidSphere();
	sphere4->Inititalize("Smile4", 1.0f, 1.0f, Vector3D(0, 20, 0));
	
	m_RigidRenders.push_back(sphere);
	m_RigidRenders.push_back(sphere2);
	m_RigidRenders.push_back(sphere3);
	m_RigidRenders.push_back(sphere4);
	//m_RigidRenders.push_back(box);

	
	

	LoadShapes("Characters/LevelInfo.txt");
}

//--------------------------------------------------------------------------------
// Text file format:
// First number shape 0 - Cube 1 - Pyramid 2 - Tetrahedon
// Second number shape length
// Third number 0 - Collectable 1 - Ebeny
// Forth Fith and Sixth number X Y Z position.
void Level::LoadShapes(std::string filePath)
{
	std::ifstream inputFile(filePath);
	std::string line;
	
	while (std::getline(inputFile, line))
	{
		std::vector<int> values;
		size_t pos = 0;
		std::string token;
		int position = 0;
		while ((pos = line.find(" ")) != std::string::npos)
		{
			token = line.substr(0, pos);
			line.erase(0, pos + 1);
			int value = GetValue(token, position);
			if (value != -1)
			{
				values.push_back(value);
			}
			position++;
		}

		values.push_back(GetValue(line, position));

		if (values.size() != 6)
		{
			return;
		}
		Shape* shapeToAdd;
		std::string filePath;
		switch (values[0])
		{
			case 0:
				shapeToAdd = new Cube();
				filePath = "Smile2";
				break;
			case 1:
				shapeToAdd = new Pyramid();
				filePath = "Smile3";
				break;
			case 2:
				shapeToAdd = new Tetrahedron();
				filePath = "Smile5";
				break;
			default:
				continue;
				break;
		}
		if (values[2] == 0)
		{
			m_Collectables.push_back(shapeToAdd);
		}
		else
		{
			m_Enemies.push_back(new EnemyAI(m_Player, shapeToAdd, 5.0f));
			filePath = "Smile4";
		}
		shapeToAdd->Inititalize(Vector3D((float)values[3], (float)values[4], (float)values[5]), filePath, (float)values[1]);
		AddShape(shapeToAdd);
	}
}

//--------------------------------------------------------------------------------
int Level::GetValue(std::string word, int position)
{
	std::string::size_type sz;
	switch (position)
	{
		case 0:
			if (word == "CUBE")
			{
				return 0;
			}
			else if (word == "PYRAMID")
			{
				return 1;
			}
			else if (word == "TETRAHEDRON")
			{
				return 2;
			}
			return -1;
		case 1:
			return -1;
		case 3:
			return word == "COLLECTABLE" ? 0 : 1;
		case 4:
			return -1;
		default:
			return std::stoi(word, &sz);
	}
}

//--
void Level::UpdateAI()
{
	for each(EnemyAI* enemyAI in m_Enemies)
	{
		enemyAI->Update();
	}
}

//--------------------------------------------------------------------------------
void Level::AddShape(Shape* shape)
{
	std::vector<RenderObject*> objects = shape->GetRenderObjects();
	m_RenderObjects.insert(m_RenderObjects.end(), objects.begin(), objects.end());
	std::vector<RodContactGenerator*> rods = shape->GetRods();
	m_ContactGenerators.insert(m_ContactGenerators.end(), rods.begin(), rods.end());
	m_Shapes.push_back(shape);
}

std::vector<Shape*> Level::GetCollidingCollectables()
{
	std::vector<Shape*> collectables;
	for (unsigned int i = 0; i < m_Collectables.size(); i++)
	{
		if (m_Collectables[i]->GetRenderObjects()[0]->GetPosition().CalculateDistance(m_Player->GetPosition()) < 5)
		{
			collectables.push_back(m_Collectables[i]);
			m_Collectables.erase(m_Collectables.begin() + i);
			i--;
		}
	}
	return collectables;
}

std::vector<EnemyAI*> Level::GetCollidingEnemies()
{
	std::vector<EnemyAI*> enemies;
	for each(EnemyAI* enemyAI in m_Enemies)
	{
		if (!enemyAI->CheckPlayerAttached() && enemyAI->GetPlayerDistance() < 4)
		{
			enemies.push_back(enemyAI);
		}
	}

	return enemies;
}

//--------------------------------------------------------------------------------
void Level::Draw()
{
	/*
	for (unsigned int i = 0; i < m_RenderObjects.size(); i++)
	{
		m_RenderObjects[i]->Draw();
	}
	*/
	for (unsigned int i = 0; i < m_RigidRenders.size(); i++)
	{
		m_RigidRenders[i]->Draw();
	}
	m_Ground->Draw();
	//m_Player->Draw();
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
	m_Player = nullptr;
	for (unsigned int i = 0; i < m_RenderObjects.size(); i++)
	{
		delete m_RenderObjects[i];
	}
	for (unsigned int i = 0; i < m_Shapes.size(); i++)
	{
		delete m_Shapes[i];
	}
	m_Shapes.clear();
	m_RenderObjects.clear();
	m_ContactGenerators.clear();
}