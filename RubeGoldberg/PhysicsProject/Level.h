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
#include "Shape.h"
#include "EnemyAI.h"
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
	void AddShape(Shape* shape);
	Player* GetPlayer() { return m_Player; };
	inline int GetNumCollectables() { return (int)m_Collectables.size(); };
	inline int GetNumEnemies() { return (int)m_Enemies.size(); };

	void UpdateAI();

	std::vector<Shape*> GetCollidingCollectables();
	std::vector<EnemyAI*> GetCollidingEnemies();

	void LoadShapes(std::string filePath);
private:
	std::vector<RenderObject*> m_RenderObjects;
	std::vector<ContactGenerator*> m_ContactGenerators;
	std::map<SpringForceGenerator*, std::vector<PhysicsObject*>> m_SpringForceGenerators;
	std::vector<Shape*> m_Collectables;
	std::vector<Shape*> m_Shapes;
	std::vector<EnemyAI*> m_Enemies;
	int GetValue(std::string, int position);
	
	Ground* m_Ground;
	Player* m_Player;
};
#endif
//======================================================================