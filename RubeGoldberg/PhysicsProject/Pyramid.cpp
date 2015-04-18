//======================================================================
//File: Level.h
//Author: Jake Ellenberg
//Created: 3/21/2015
//Purpose: Hold level data
//======================================================================
#include "Pyramid.h"

//--------------------------------------------------------------------------------
Pyramid::Pyramid()
{
}

//--------------------------------------------------------------------------------
Pyramid::~Pyramid()
{
}

//--------------------------------------------------------------------------------
void Pyramid::Inititalize(Vector3D centerPosition, std::string texturePath, float length)
{
	Vector3D topPos = centerPosition;
	topPos.Y += length / 2.0f;
	Vector3D topLeftPos = centerPosition;
	topLeftPos.X -= length / 2.0f;
	topLeftPos.Y += length / 2.0f;
	topLeftPos.Z -= length / 2.0f;
	Vector3D topRightPos = topLeftPos;
	topRightPos.X += length;
	Vector3D botLeftPos = topLeftPos;
	botLeftPos.Y -= length;
	Vector3D botRightPos = topRightPos;
	botRightPos.Y -= length;

	Vector3D botLeftPosClose = botLeftPos;
	botLeftPosClose.Z += length;
	Vector3D botRightposClose = botRightPos;
	botRightposClose.Z += length;

	std::string filePath = texturePath;

	RenderObject* topObject = new RenderObject();
	topObject->Inititalize(1.0f, topPos, filePath);
	m_Objects.push_back(topObject);
	RenderObject* botLeftObject = new RenderObject();
	botLeftObject->Inititalize(1.0f, botLeftPos, filePath);
	m_Objects.push_back(botLeftObject);
	RenderObject* botRightObject = new RenderObject();
	botRightObject->Inititalize(1.0f, botRightPos, filePath);
	m_Objects.push_back(botRightObject);
	RenderObject* botLeftObjectClose = new RenderObject();
	botLeftObjectClose->Inititalize(1.0f, botLeftPosClose, filePath);
	m_Objects.push_back(botLeftObjectClose);
	RenderObject* botRightObjectClose = new RenderObject();
	botRightObjectClose->Inititalize(1.0f, botRightposClose, filePath);
	m_Objects.push_back(botRightObjectClose);

	//connect the bottom
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botLeftObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botRightObject, botRightObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botRightObject, length));
	m_Rods.push_back(new RodContactGenerator(botLeftObjectClose, botRightObjectClose, length));
	m_Rods.push_back(new RodContactGenerator(botLeftObject, botRightObjectClose, botLeftPos.CalculateDistance(botRightposClose)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, botLeftObjectClose, botLeftPosClose.CalculateDistance(botRightPos)));

	m_Rods.push_back(new RodContactGenerator(botLeftObject, topObject, topPos.CalculateDistance(botLeftPos)));
	m_Rods.push_back(new RodContactGenerator(botRightObject, topObject, topPos.CalculateDistance(botRightPos)));
	m_Rods.push_back(new RodContactGenerator(botRightObjectClose, topObject, topPos.CalculateDistance(botRightposClose)));
	m_Rods.push_back(new RodContactGenerator(botLeftObjectClose, topObject, topPos.CalculateDistance(botLeftPos)));
}