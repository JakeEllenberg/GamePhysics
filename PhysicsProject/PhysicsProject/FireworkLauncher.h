//======================================================================
//File: FireWorkLauncher.h
//Author: Jake Ellenberg
//Created: 1/24/2015
//Purpose: Containts fireworks and managers making more on explosion
//======================================================================
#ifndef FIREWORKLAUNCHER_H
#define FIREWORKLAUNCHER_H
//======================================================================
#include <vector>
#include "Firework.h"
#include <stdlib.h>
#include <time.h>
//======================================================================
class FireworkLauncher
{
public:
	FireworkLauncher();
	~FireworkLauncher();

	void Initialzie(Vector3D startPos, Vector3D startVelocity, int startLifeTime, int minExpFireworks, int maxExpFireworks, int minLifeTime, int maxLifeTime, int expChance, float minSpeed, float maxSpeed, int maxFireWorks, int numLevels);
	void Update(int deltaTime);
	void Draw();
	void CleanUp();
	void Reset();
private:
	int getNumExp();
	int getLifeTime();
	bool getIsExploading();
	float getSpeed();
	Vector3D getVelocity(float speed);
	void GenerateExplosion(Vector3D startPos);

	std::vector<Firework*> m_Fireworks;
	int m_MinExpFireworks;
	int m_MaxExpFireworks;
	int m_MinLifeTime;
	int m_MaxLifeTime;
	int m_ExpChance;
	float m_MinSpeed;
	float m_MaxSpeed;
	int m_MaxFireworks;
	Vector3D m_StartPosition;
	Vector3D m_StartVelocity;
	int m_StartLifeTime;
	int m_NumLevels;
	int m_CurrentLevel;
};
#endif
//======================================================================