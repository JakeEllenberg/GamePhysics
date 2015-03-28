//======================================================================
//File: Level.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Hold level data
//======================================================================
#ifndef LEVEL_H
#define LEVEL_H
//======================================================================
#include "RenderObject.h"
#include "Ground.h"
#include <vector>
#include <map>
#include "Player.h"
class SpringForceGenerator;
class ContactGenerator;
//======================================================================
class Level
{
public:
	Level();
	~Level();

	void Initialize();
	void CleanUp();
	void Draw();

	Ground* GetGround() { return m_Ground; };
	std::vector<PhysicsObject*> GetCollisionObjects();
	std::vector<ContactGenerator*> GetContactGenerators();
	std::map<SpringForceGenerator*, std::vector<PhysicsObject*>> GetSpringForceGenerators();
private:
	std::vector<RenderObject*> m_RenderObjects;
	std::vector<ContactGenerator*> m_ContactGenerators;
	std::map<SpringForceGenerator*, std::vector<PhysicsObject*>> m_SpringForceGenerators;
	Ground* m_Ground;
	Player* m_Player;
};
#endif
//======================================================================